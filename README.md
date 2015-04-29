# otucha [![Build Status](https://travis-ci.org/dpwolfe/otucha.svg?branch=master)](https://travis-ci.org/dpwolfe/otucha) [![Coverage Status](https://coveralls.io/repos/dpwolfe/otucha/badge.svg?branch=master)](https://coveralls.io/r/dpwolfe/otucha?branch=master)

A cross-platform C++ OpenGL program that also compiles to JavaScript using Emscripten.

#### Status

- Builds and runs on Windows, Mac OS X and Linux as well as in browser with Emscripten
- Currently working on increasing code coverage and moving external dependencies to submodules, upgrading them in the process

#### Developer Setup
Follow these steps for Windows or Mac development.  Pay careful attention to any platform specific instructions each vendor provides.

1. Install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)
3. Install [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/)
4. Install [Grunt](http://gruntjs.com/) from [here](http://gruntjs.com/getting-started)
5. Install [Bower](http://bower.io/)
6. Run the following command from the repository root:

   ```
   npm install
   grunt init
   ```

#### Building with Emscripten
1. Run the following command from the repository root:

  ```
  grunt build:js
  ```
2. Open the index.html in the /www directory in Firefox or Chrome

#### Grunt options
**--jsMin** - Runs uglify (mangle + compress) on the output Emscripten JS.

**--jsUseDist** - Uses the otucha.js and index.html from the dist directory instead of building them with Emscripten.  Used for git deploy on a server that does not have CMake and Emscripten available.

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

A perspective view of a cube with copper material properties and three lights in positions selected in order to produce specular highlights.  A sample of rendered text also appears on the bottom left corner.

[Screenshot of just the Copper Cube](https://onedrive.live.com/embed?cid=EB3994E07F023E78&resid=EB3994E07F023E78%2142597&authkey=AAuP3j8_a2lGV1A)

[Live Demo of just the cube](http://spritegeist.azurewebsites.net/)


#### Code names
Like otucha, these code names have no special meaning and are picked using the random page feature on Wikipedia.  They are used for namespaces of discrete areas of the app that have separate concerns at the moment. They are:

**RFFalcon**: Short for red-footed falcon.  Geometry, models and rendering.  Point and Matrix classes including vec union structs. Text built on freetype.

**Terasca**: MVC application classes.

**Warbler**: Console implementation.
