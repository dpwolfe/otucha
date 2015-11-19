# otucha [![Build Status](https://travis-ci.org/dpwolfe/otucha.svg?branch=master)](https://travis-ci.org/dpwolfe/otucha) [![Coverage Status](https://coveralls.io/repos/dpwolfe/otucha/badge.svg?branch=master)](https://coveralls.io/r/dpwolfe/otucha?branch=master)

A cross-platform OpenGL program written in C++. Builds and runs natively on Windows, OSX and Linux. Runs in Chrome, Firefox and Safari when built with Emscripten.

### In Progress
- Increasing code coverage using the custom OpenGL and GLEW mock lib

### Developer Setup
1. Install the following, paying careful attention to any platform specific instructions:
  - [CMake](http://www.cmake.org/) - (currently using 3.4.0-rc2)
    - OSX: Launch the CMake app after copying it to your _Applications_ and follow the instructions found under _Tools > How to Install For Command Line Use_
  - [Emscripten](http://kripken.github.io/emscripten-site/) from [here](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html) - (currently using 1.35.4)
    - OSX:
      - Put the extracted `emsdk_portable` in your home directory
      - Follow the [Platform-specific notes](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html#platform-notes-installation-instructions-portable-sdk)
      - You can install Python 2.7.10 [here](https://www.python.org/downloads/release/python-2710/) instead of doing the last step in the Platform-specific notes since that step may not work. _Do not use Python 3._
      - Open a command prompt in the `emsdk_portable` directory and run these commands:

        ```shell
        ./emsdk update
        ./emsdk install latest
        ./emsdk activate latest
        source ./emsdk_env.sh
        ```
  
      - Add the following line to your ~/.bash_profile:

        ```shell
        alias initem='source ./emsdk_portable/emsdk_env.sh'
        ```
        
      - Before compiling JavaScript, make sure you have run this in your command prompt once:
      
        ```shell
        initem
        ```
  
    - Windows: [Activate the MinGW toolchain](http://kripken.github.io/emscripten-site/docs/building_from_source/toolchain_what_is_needed.html?highlight=mingw).
  - [NodeJS](http://nodejs.org/) from [here](http://nodejs.org/download/) - (currently using 4.2.1)
    - Emscripten uses a different version when you run `initem` 
  - [Grunt](http://gruntjs.com/) - (currently using 0.1.13)
    - Windows: Run the following in a command prompt:

      ```shell
      npm install -g grunt-cli
      ```

    - OSX: Run the following in a command prompt:

      ```shell
      sudo npm install -g grunt-cli
      ```

  - [Bower](http://bower.io/) - (currently using 1.6.5)
    - Windows: Run the following in a command prompt:
    
      ```shell
      npm install -g bower
      ```

    - OSX: Run the following in a command prompt:
    
      ```shell
      sudo npm install -g bower
      ```

2. Run the following command from the repository root:

   ```
   npm install
   ```

3. Update the version of npm that came with NodeJS to the latest:
  - OSX: Run the following in a command prompt:

    ```shell
    sudo npm install npm -g
    ```

  - Windows:
    - Run the following in a command prompt:

      ```shell
      npm install npm -g
      ```

    - Delete the `npm` and `npm.cmd` files from the `\Program Files\nodejs` directory.

### Building web
1. Run the following command in the repository root after running `initem`:

  ```shell
  grunt build:js
  ```

2. Open www/index.html in Chrome, Firefox or Safari (OSX)

### Grunt options
**--jsMin** - Runs uglify with mangle and compress options on the output JavaScript

**--jsUseDist** - _Support is temporarily removed._ Uses pre-built JS and HTML for git deploy on a server that does not have CMake and Emscripten available.

### Building native
1. Run the following command from the repository root:

  ```shell
  grunt
  ```

2. Build using the generated files under the `build` directory.  For example, if developing on Windows with Visual Studio, open the otucha.sln, build and run.  If developing on Mac or Linux, build using the Makefile.

### Building with Xcode
1. Run the following command from the repository root:

  ```shell
  grunt cmake:xcode
  ```

  Xcode will launch when completed.

2. Switch the target from _ALL\_BUILD_ to _otucha_
3. Build and run

### What you'll see
A perspective view of a copper cube and three lights in positions that produce specular highlights.  Some rendered text also appears on the bottom left corner.

[Live Demo](http://spritegeist.azurewebsites.net/)

### Code names
Like otucha, these code names have no special meaning and are picked using the random page feature on Wikipedia.  They are used for namespaces.

**RFFalcon**: Short for Red-Footed Falcon.  Geometry, models and rendering.  Point and Matrix classes including vec union structs. Text rendering with C++ OpenGL layer on top of FreeType.

**Terasca**: Simple MVC application framework utilizing GLFW and GLEW.

**Warbler**: Console and logging.
