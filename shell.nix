let
  pkgs = import (fetchTarball "channel:nixos-24.05") { };
in
pkgs.mkShellNoCC {
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
    libglvnd
    libglvnd.dev
  ];
  shellHook = ''
    mkdir vendor -p
    sudo cp ${pkgs.glfw} ./vendor/glfw -r
    sudo cp ${pkgs.vulkan-headers} ./vendor/vulkan_header -r
    sudo cp ${pkgs.vulkan-loader} ./vendor/vulkan_loader -r
    sudo cp ${pkgs.glm} ./vendor/glm -r
    sudo cp ${pkgs.libglvnd.dev} ./vendor/gl -r
  '';
}
