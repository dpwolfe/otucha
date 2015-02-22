# otucha
An OpenGL program that compiles from C++ to JavaScript using Emscripten

#### Status

- Builds and runs on Windows natively and in browser with Emscripten

#### Developer Setup
1. Install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)
3. Install [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/)
4. Install [Grunt](http://gruntjs.com/) from [here](http://gruntjs.com/getting-started)
5. Run the following command from the repository root:

   ```
   npm install
   ```

#### Building with Emscripten using CMake
1. Run the following command from the repository root:

  ```
  grunt build:js
  ```

#### Building native
1. Run the following command from the repository root:

  ```
  grunt
  ```
2. Build. For example, open the otucha.sln and build if developing on Windows with Visual Studio

#### What you'll see

A perspective view of a cube with copper material properties and three lights in positions selected in order to produce specular highlights.

[Image of Copper Cube](https://onedrive.live.com/embed?cid=EB3994E07F023E78&resid=EB3994E07F023E78%2142597&authkey=AAuP3j8_a2lGV1A)
