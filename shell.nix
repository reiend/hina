let
  pkgs = import (fetchTarball "channel:nixos-24.05") { };
in
pkgs.mkShellNoCC {
  packages = with pkgs; [
    cmake
    clang_18
    ninja
  ];
}
