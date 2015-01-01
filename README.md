# otucha
A sample OpenGL program that compiles from C++ to JavaScript using Emscripten


## Developer Setup
1. Download and install Emscripten from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Download and install [MingW](http://mingw.org/) from [here](http://mingw.org/download/installer)
3. Download the GLEW 1.11.0 source zip from [here](http://sourceforge.net/projects/glew/files/glew/1.11.0/)
4. Build the GLEW source in MingW with the make command
5. Copy the compiled lib/glew32.a binary to the /external/lib directory
6. Download the GLFW 32-bit Windows binaries from [here](http://www.glfw.org/download.html)
8. Copy \lib-mingw\libglfw3.a to the /external/lib directory

##### Environment for Makefile

1. Define the CXX environment variable depending on desired compilation.
   - _emcc_ for Emscripten compilation
   - _cpp_, _gcc_, _clang++_, etc. for c++ compilation.
