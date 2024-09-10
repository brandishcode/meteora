{
  description = "Meteora development environment";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    nixvim.url = "github:brandishcode/nixvim-configuration";
  };

  outputs = { nixpkgs, nixvim, ... }:
    let
      # system should match the system you are running on
      system = "x86_64-linux";
      editor = nixvim.packages.${system}.opengl;
      pkgs = import nixpkgs { inherit system; };
    in {
      packages."${system}" = {
        inherit editor;
        default = pkgs.callPackage ./default.nix { inherit editor; };
      };
    };
}
