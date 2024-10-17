{
  pkgs ? import (fetchTarball "channel:nixos-24.05") { },
}:
let
  BUILD_TYPE = {
    DEBUG = "Debug";
    RELEASE = "RELEASE";
  };

  GENERATOR = {
    NINJA = "Ninja";
  };
  run_app =
    {
      project_name,
      source_dir,
      build_dir,
      binary_dir,
      generator,
      build_type,
    }:
    let
      to_lower = pkgs.lib.strings.toLower;
    in
    pkgs.writeShellScriptBin "run_app_${to_lower build_type}" ''
      rm -rf .cache build
      cmake \
        -S ${source_dir} \
        -B ${build_dir} \
        -G ${generator} \
        -DCMAKE_BUILD_TYPE=${build_type} \
        --fresh
        ${to_lower generator} -C ${build_dir} 
        ${binary_dir}
    '';
in
{
  run_app_release = run_app rec {
    project_name = "hina";
    source_dir = ".";
    build_dir = "build";
    binary_dir = "${build_dir}/bin/${project_name}";
    generator = GENERATOR.NINJA;
    build_type = BUILD_TYPE.RELEASE;
  };

  run_app_debug = run_app rec {
    project_name = "hina";
    source_dir = ".";
    build_dir = "build";
    binary_dir = "${build_dir}/bin/${project_name}";
    generator = GENERATOR.NINJA;
    build_type = BUILD_TYPE.DEBUG;
  };
}
