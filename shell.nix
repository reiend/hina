let
  pkgs = import (fetchTarball "channel:nixos-24.05") { };
in
pkgs.mkShellNoCC {
  test1 = "${pkgs.vulkan-headers}";
  test2 = "${pkgs.glfw}/include";
  test3 = "${pkgs.glm}";
  test4 = "${pkgs.libGL}";
  test5 = "${pkgs.libGLU}";
  test6 = "${pkgs.glew}";
  test7 = "${pkgs.mesa}";
  test8 = "${pkgs.libglvnd}";
  test9 = "${pkgs.libglvnd.dev}";
  test10 = "${pkgs.libGL.dev}";
  test11 = "${pkgs.clang_18}";
  packages = with pkgs; [
    cmake
    clang_18
    ninja
    vulkan-tools
    vulkan-headers
    vulkan-loader
    vulkan-validation-layers
    spirv-tools
    spirv-headers
    glfw
    glm
    shaderc
    xorg.libpthreadstubs
    xorg.libX11
    xorg.libXxf86vm
    xorg.libXrandr
    xorg.libXi
    libGL
    libGL.dev
    libglvnd
    libglvnd.dev
  ];
}
