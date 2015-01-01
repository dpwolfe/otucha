# otucha
A sample OpenGL program that compiles from C++ to JavaScript using Emscripten


## Developer Setup
1. Download and install Emscripten from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Download the GLEW distributable zip from [here](http://glew.sourceforge.net/)
2. Copy the glew32.lib to the ./external/lib directory
3. Download the GLFW 32-bit Windows binaries from [here](http://www.glfw.org/download.html)
4. Copy \lib-msvc120\glfw3.lib to the /external/lib directory
5. Copy \lib-mingw\libglfw3.a to the /external/lib directory

##### Environment for Makefile

1. Define the CXX environment variable depending on desired compilation.
   - _emcc_ for Emscripten compilation
   - _cpp_, _gcc_, _clang++_, etc. for c++ compilation.
