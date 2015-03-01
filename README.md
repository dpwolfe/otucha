# otucha
An OpenGL program that compiles from C++ to JavaScript using Emscripten

#### Status

Builds and runs on Windows natively and in browser with Emscripten

#### Developer Setup
1. Install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)
3. Install [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/)
4. Install [Grunt](http://gruntjs.com/) from [here](http://gruntjs.com/getting-started)
5. Install [Bower](http://bower.io/)
6. Run the following command from the repository root:

   ```
   npm install
   ```

#### Building with Emscripten
1. Run the following command from the repository root:

  ```
  grunt build:js
  ```
2. Open the index.html in the /www directory in Firefox or Chrome

##### Grunt options
--jsMin - Runs uglify (mangle + compress) on the output Emscripten JS.

--jsUseDist - Uses the otucha.js and index.html from the dist folder instead of building Emscripten.  Useful for git deploy on a server that does not have CMake and Emscripten available.

#### Building native
1. Run the following command from the repository root:

  ```
  grunt
  ```
2. Build using the generated project files.  For example, if developing on Windows with Visual Studio, open the otucha.sln, build and run.  If developing on Mac or Linux, this will generate a Makefile.

#### Building with Xcode
1. Run the following command from the repository root:

  ```
  grunt build:xcode
  ```
2. Open the generated xcodeproj in the xbuild directory.

#### What you'll see

A perspective view of a cube with copper material properties and three lights in positions selected in order to produce specular highlights.

[Image of Copper Cube](https://onedrive.live.com/embed?cid=EB3994E07F023E78&resid=EB3994E07F023E78%2142597&authkey=AAuP3j8_a2lGV1A)

[Live Demo](http://spritegeist.azurewebsites.net/)
