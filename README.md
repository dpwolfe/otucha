# otucha [![Build Status](https://travis-ci.org/dpwolfe/otucha.svg?branch=master)](https://travis-ci.org/dpwolfe/otucha) [![Coverage Status](https://coveralls.io/repos/dpwolfe/otucha/badge.svg?branch=master)](https://coveralls.io/r/dpwolfe/otucha?branch=master)

A cross-platform C++ OpenGL program. Builds and runs natively on Windows, OSX and Linux. Runs in Chrome, Firefox and Safari (OSX) when built with Emscripten.

### In Progress
- moving OpenGL calls to OGLplus so they can be mocked for tests

### Developer Setup
*Pay careful attention to platform specific instructions.*

1. Install [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
2. Install [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)
3. Install [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/)
4. Install [Grunt](http://gruntjs.com/) from [here](http://gruntjs.com/getting-started)
5. Install [Bower](http://bower.io/)
6. Run the following command from the repository root:

   ```
   npm install
   ```

### Building web
1. Run the following command from the repository root:

  ```
  grunt build:js
  ```
2. Open the index.html in the /www directory in Chrome, Firefox or Safari (OSX)

### Grunt options
**--jsMin** - Runs uglify (mangle + compress) on the output Emscripten JS.

**--jsUseDist** - Uses the otucha.js and index.html from the dist directory instead of building them with Emscripten.  Used for git deploy on a server that does not have CMake and Emscripten available.

### Building native
1. Run the following command from the repository root:

  ```
  grunt
  ```
2. Build using the generated project files.  For example, if developing on Windows with Visual Studio, open the otucha.sln, build and run.  If developing on Mac or Linux, this will generate a Makefile.

### Building with Xcode
1. Run the following command from the repository root:

  ```
  grunt cmake:xcode
  ```

Xcode will launch once completed.

### What you'll see
A perspective view of a cube with copper material properties and three lights in positions selected in order to produce specular highlights.  A sample of rendered text also appears on the bottom left corner.

[Live Demo](http://spritegeist.azurewebsites.net/)

### Code names
Like otucha, these code names have no special meaning and are picked using the random page feature on Wikipedia.  They are used for namespaces.

**RFFalcon**: Short for red-footed falcon.  Geometry, models and rendering.  Point and Matrix classes including vec union structs. Text rendering with C++ OpenGL layer on top of Freetype.

**Terasca**: MVC application framework utilizing GLFW and GLEW.

**Warbler**: Console and logging.
