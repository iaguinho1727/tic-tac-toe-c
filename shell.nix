{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # Name of the environment
  name = "gcc-env";

  # Packages available in the shell
  buildInputs = [
    pkgs.gnumake
    pkgs.libgcc
  ];

  # Optional: automatically create and activate a virtual environment
  shellHook = ''
    make -j 4
    sudo make install
  '';
}
