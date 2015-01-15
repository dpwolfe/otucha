# otucha
A sample OpenGL program that compiles from C++ to JavaScript using Emscripten

#### Current Status

- Supports building and running on Windows
- Use Makefile and emmake to build with Emscripten
- Support for Emscripten through CMake is next.

#### Developer Setup
1. Download and install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Download and install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)

##### Building with Emscripten
Support is currently for Windows

1. Define the CXX environment variable as _emcc_
2. Run the following command from the src directory:
  - emmake make EMCC=1

#### Building with Visual Studio
1. Run the following command from the src directory:
  - cmake .
2. Open otucha.sln, where you can build and run

