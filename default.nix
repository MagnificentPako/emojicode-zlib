with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "emojicode-zlib";
    src  = ./.;
    buildInputs = [ cmake 
                    (import "/etc/nixos/pkgs/emojicode") 
                    gcc 
                    ninja
                    zlib
                  ];
    doCheck = false;
}