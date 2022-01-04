{
  description = "CXBQN";

  outputs = { self, nixpkgs }: {

    packages.x86_64-linux.cxbqn =
      let pkgs = import nixpkgs { system = "x86_64-linux"; };
      in pkgs.stdenv.mkDerivation {
        pname = "CXBQN";
        version = "0.11.0";
        src = pkgs.fetchgit {
          url = "https://github.com/ashermancinelli/cxbqn.git";
          rev = "4816322";
          sha256 = "sha256-ruf4ycwSyJ36eczA4n1cdokRdO6X/+PfcOUnEK/i3as=";
        };
        nativeBuildInputs = with pkgs; [
          gcc11
          cmake
        ];
      };

    defaultPackage.x86_64-linux = self.packages.x86_64-linux.cxbqn;

  };
}
