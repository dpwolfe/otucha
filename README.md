# otucha
A sample OpenGL program that compiles from C++ to JavaScript using Emscripten


## Developer Setup

#### Setup for Windows compilation
1. Install Visual Studio 2013

#### Building in Windows
1. Open the sln and build.

#### Setup for Emscripten compilation
1. Download and install Emscripten from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Download and install [MingW](http://mingw.org/) from [here](http://mingw.org/download/installer)
3. Download the GLEW 1.11.0 source zip from [here](http://sourceforge.net/projects/glew/files/glew/1.11.0/)
4. Build the GLEW source in MingW with the make command
5. Copy the compiled lib/glew32.a binary to otucha/external/lib
6. Build the GLEW source in Visual Studio with the Release configuration
7. Copy the compiled lib/Release/Win32/glew32.lib to otucha/external/lib
8. Download the GLFW 32-bit Windows binaries from [here](http://www.glfw.org/download.html)
9. Copy \lib-mingw\libglfw3.a to otucha/external/lib
10. Copy \lib-msvc120\glfw3.lib to otucha/external/lib
11. From the MingW install directory, copy /lib/libglu32.a to otucha/external/lib

##### Environment for Makefile
1. Define the CXX environment variable depending on desired compilation.
   - _emcc_ for Emscripten compilation
   - _cpp_, _gcc_, _clang++_, etc. for c++ compilation.

#### Building with Emscripten
1. Run the following command from the src directory:
- emmake make EMCC=1

