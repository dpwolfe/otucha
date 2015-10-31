# otucha [![Build Status](https://travis-ci.org/dpwolfe/otucha.svg?branch=master)](https://travis-ci.org/dpwolfe/otucha) [![Coverage Status](https://coveralls.io/repos/dpwolfe/otucha/badge.svg?branch=master)](https://coveralls.io/r/dpwolfe/otucha?branch=master)

A cross-platform OpenGL program written in C++. Builds and runs natively on Windows, OSX and Linux. Runs in Chrome, Firefox and Safari when built with Emscripten.

### In Progress
- Increasing code coverage using the custom OpenGL and GLEW mock lib

### Developer Setup
1. Install the following, paying careful attention to any platform specific instructions:
  - [CMake](http://www.cmake.org/) from [here](http://www.cmake.org/files/v3.1/?C=M;O=D)
  - [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
    - Windows: [Activate the MinGW toolchain](http://kripken.github.io/emscripten-site/docs/building_from_source/toolchain_what_is_needed.html?highlight=mingw).
  - [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/)
  - [Grunt](http://gruntjs.com/)
    - Windows: `npm install -g grunt-cli`
    - OSX: `sudo npm install -g grunt-cli`
  - [Bower](http://bower.io/)
    - Windows: `npm install -g bower`
    - OSX: `sudo npm install -g bower`
2. Run the following command from the repository root:

   ```
   npm install
   ```
3. Update the version of npm that came with NodeJS to the latest:
  - Linux: `sudo npm install npm -g`
  - Windows: `npm install npm -g` and delete the `npm` and `npm.cmd` files from the `\Program Files\nodejs` directory.

### Building web
1. Run the following command from the repository root:

  ```
  grunt build:js
  ```
2. Open www/index.html in Chrome, Firefox or Safari (OSX)

### Grunt options
**--jsMin** - Runs uglify with mangle and compress options on the output JavaScript

**--jsUseDist** - Support is temporarily removed. Uses pre-built JS and HTML for git deploy on a server that does not have CMake and Emscripten available.

### Building native
1. Run the following command from the repository root:

  ```
  grunt
  ```
2. Build using the generated files under the `build` directory.  For example, if developing on Windows with Visual Studio, open the otucha.sln, build and run.  If developing on Mac or Linux, build using the Makefile.

### Building with Xcode
1. Run the following command from the repository root:

  ```
  grunt cmake:xcode
  ```
  Xcode will launch when completed.

### What you'll see
A perspective view of a copper cube and three lights in positions that produce specular highlights.  Some rendered text also appears on the bottom left corner.

[Live Demo](http://spritegeist.azurewebsites.net/)

### Code names
Like otucha, these code names have no special meaning and are picked using the random page feature on Wikipedia.  They are used for namespaces.

**RFFalcon**: Short for Red-Footed Falcon.  Geometry, models and rendering.  Point and Matrix classes including vec union structs. Text rendering with C++ OpenGL layer on top of FreeType.

**Terasca**: Simple MVC application framework utilizing GLFW and GLEW.

**Warbler**: Console and logging.
