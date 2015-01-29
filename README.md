# otucha
An OpenGL program that compiles from C++ to JavaScript using Emscripten

#### Current Status

- Supports building and running on Windows with CMake
- Supports building Emscripten using a Makefile
- Next: Emscripten makefile with CMake

#### Developer Setup
1. Download and install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Download and install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)

#### Building with Emscripten
Support is currently for Windows

1. Define the CXX environment variable as _emcc_
2. Run the following command from the src directory:
```
emmake make EMCC=1
```

#### Building with Visual Studio
1. Run the following command from the src directory:

  ```
  cmake .
  ```
2. Open otucha.sln
3. Build and run the otucha project

#### What you'll see

A perspective view of a cube with copper material properties and three lights in positions that produce specular highlights.

[Image of Copper Cube](https://onedrive.live.com/embed?cid=EB3994E07F023E78&resid=EB3994E07F023E78%2142597&authkey=AAuP3j8_a2lGV1A)

