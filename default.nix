{ editor, makeWrapper, llvmPackages, pkg-config, cmake, spdlog, glfw-wayland
, glew, glm, stb, libGLU, ... }:

let vendorLibraries = [ spdlog ];
in llvmPackages.stdenv.mkDerivation rec {

  pname = "Meteora";
  version = "0.0.1";

  src = ./.;

  # Dependencies that should exist in the runtime environment
  buildInputs = [ glfw-wayland glew glm libGLU ] ++ vendorLibraries;
  # Dependencies that should only exist in the build environment
  nativeBuildInputs = [ makeWrapper pkg-config cmake ] ++ [ editor ];

  buildPhase = ''
    cmake ../
    cmake --build .
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp ${pname} $out/bin
  '';

  shellHook = ''
    export PKG_CONFIG_PATH=${stb}/lib/pkgconfig
    echo "Development Shell Started"
    runPhase configurePhase
    cd ../
  '';
}
