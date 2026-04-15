{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs, ... }: let
    systems = ["x86_64-linux" "aarch64-linux" "aarch64-darwin"];
    forAllSystems = nixpkgs.lib.genAttrs systems;
    pkgsFor = system: import nixpkgs {
      inherit system;
    };
  in {
    devShells = forAllSystems (system: let
      pkgs = pkgsFor system;
    in {
      default = pkgs.mkShell rec {
        buildInputs = with pkgs; [
          shaderc glslang shader-slang
          cmake ninja clang stdenv.cc.cc.lib
          pkg-config python314 python314Packages.jinja2 libGL
        ] ++ lib.optionals (system == "x86_64-linux") [
          renderdoc mold tracy
          libX11 libXcursor libXrandr libXi libXinerama libxcb
          wayland wayland-protocols wayland-scanner libxkbcommon libffi
        ];

        shellHook = ''
          export CC="${pkgs.clang}/bin/clang"
          export CXX="${pkgs.clang}/bin/clang++"
        '' + pkgs.lib.optionalString (system == "x86_64-linux") ''
          export LDFLAGS="-fuse-ld=${pkgs.mold}/bin/mold -flto $LDFLAGS"
          export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${builtins.toString (pkgs.lib.makeLibraryPath buildInputs)}";
        '' + pkgs.lib.optionalString (system == "aarch64-darwin") ''
          export DYLD_LIBRARY_PATH="$DYLD_LIBRARY_PATH:${builtins.toString (pkgs.lib.makeLibraryPath buildInputs)}";
         '';
      };
    });
  };
}
