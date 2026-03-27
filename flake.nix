{
  description = "A sophisticated dev environment for Raylib Pong";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux"; # Adjust if you're on ARM
      pkgs = import nixpkgs { inherit system; };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gcc
          pkg-config
          cmake
        ];

        buildInputs = with pkgs; [
          raylib
          wayland
          libGL
          libxkbcommon
          xorg.libX11
          xorg.libXcursor
          xorg.libXinerama
          xorg.libXrandr
        ];

        # This part is the secret sauce for NixOS graphics
        shellHook = ''
          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath (with pkgs; [
            libGL
            libxkbcommon
            wayland
          ])}:$LD_LIBRARY_PATH
          echo "Welcome back, rye. Your Raylib environment is ready."
        '';
      };
    };
}