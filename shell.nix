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
    python3
  ];
  vendor_glfw = "${pkgs.glfw}";
  vendor_vulkan_header = "${pkgs.vulkan-headers}";
  vendor_vulkan_loader = "${pkgs.vulkan-loader}";
  vendor_glm = "${pkgs.glm}";
  vendor_gl = "${pkgs.libglvnd.dev}";
  shellHook = ''
    python ./run.py
  '';
}
