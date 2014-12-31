# otucha
A sample OpenGL program that compiles from C++ to JavaScript using Emscripten


## Developer Setup
This is currently developed with Visual Studio 2013 Ultimate.

1. Download the GLEW distributable zip from [here](http://glew.sourceforge.net/)
2. Copy the glew32.lib to the ./external/lib directory
3. Download the GLFW 32-bit Windows binaries from [here](http://www.glfw.org/download.html)
4. Copy the \lib-msvc120\glfw3.lib to the /external/lib directory
5. TODO: Steps for dlls

### Environment for Makefile

1. Define the CXX environment variable depending on desired compilation.
   - _emcc_ for Emscripten compilation
   - _cpp_, _gcc_, etc. for c++ compilation.
