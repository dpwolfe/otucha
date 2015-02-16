# otucha
An OpenGL program that compiles from C++ to JavaScript using Emscripten

#### Status

- Builds and runs on Windows as native and Emscripten client

#### Developer Setup
1. Install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)

#### Building with Emscripten using CMake
1. Run the following commands from the src directory:

  ```
  emcmake cmake .
  make
  ```

#### Building native
1. Run the following command from the src directory:

  ```
  cmake . -DOTUCHA_EMSCRIPTEN_ENABLED=OFF
  ```
2. Open otucha.sln
3. Build and run the otucha project

#### What you'll see

A perspective view of a cube with copper material properties and three lights in positions selected in order to produce specular highlights.

[Image of Copper Cube](https://onedrive.live.com/embed?cid=EB3994E07F023E78&resid=EB3994E07F023E78%2142597&authkey=AAuP3j8_a2lGV1A)

