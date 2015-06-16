module.exports = function (grunt) {
    var path = require('path');
    require('load-grunt-tasks')(grunt);

    var coverallsVerbose = grunt.option('coverallsVerbose') ? '-DCOVERALLS_VERBOSE=ON ' : '';
    
    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        update_submodules: {
            default: {}
        },
        shell: {
            options: {
                stderr: false
            },
            target: {
                command: 'echo Use build:js or cmake:native'
            },
            native: {
                command: [
                    'echo Running CMake for native',
                    'cd build',
                    'cmake -DOTUCHA_DO_NOT_WARN_GL_H=ON ..'
                ].join('&&')
            },
            coveralls: {
                command: [
                    'echo Running CMake for Coveralls',
                    'cd cbuild',
                    'cmake -DOTUCHA_DO_NOT_WARN_GL_H=ON -DCOVERALLS=ON ' + coverallsVerbose + '-DCMAKE_BUILD_TYPE=Debug ..'
                ].join('&&')
            },
            xcode: {
                command: [
                    'echo Running CMake for Xcode',
                    'cd xbuild',
                    'cmake -DOTUCHA_DO_NOT_WARN_GL_H=ON -G Xcode ..',
                    'echo Opening Xcode...',
                    'open -a Xcode otucha.xcodeproj'
                ].join('&&')
            },
            emscripten_cmake: {
                options: {
                    failOnError: false
                },
                command: [
                    'cd embuild',
                    'emcmake cmake -DOTUCHA_EMSCRIPTEN_ENABLED=ON -G "MinGW Makefiles" ..'
                ].join('&&')
            },
            emscripten_make: {
                command: [
                    'cd embuild',
                    'make'
                ].join('&&')
            }
        },
        bowercopy: {
            server: {
                options: {
                    srcPrefix: 'src/server',
                    destPrefix: 'www'
                },
                files: {
                    'server.js': 'server.js'
                }
            },
            html: {
                options: {
                    srcPrefix: 'src/server',
                    destPrefix: 'www'
                },
                files: {
                    'index.html': 'index.html'
                }
            },
            js: {
                options: {
                    srcPrefix: 'embuild',
                    destPrefix: 'www'
                },
                files: {
                    'otucha.js': 'otucha.js',
                }
            }
        },
        uglify: {
            options: {
                sourceMap: false,
                banner: '/*! <%= pkg.name %> <%= grunt.template.today("yyy-mm-dd-HH-MM-ss") %> */\n',
                compress: true,
                mangle: true
            },
            build: {
                files: {
                    'www/otucha.js': [
                        'embuild/otucha.js'
                    ]
                }
            }
        }
    });

    grunt.registerTask('default', ['cmake']);
    grunt.registerTask('cmake', ['cmake:native']);
    grunt.registerTask('cmake:native', function () {
        grunt.file.mkdir('build');
        grunt.task.run(['shell:native']);
    });
    grunt.registerTask('cmake:coveralls', function () {
        grunt.file.mkdir('cbuild');
        grunt.task.run(['shell:coveralls']);
    });
    grunt.registerTask('cmake:xcode', function () {
        grunt.file.mkdir('xbuild');
        grunt.task.run(['shell:xcode']);
    });
    grunt.registerTask('build:js', function () {
        if (grunt.option('jsUseDist')) {
            grunt.fail('jsUseDist is not supported at the moment.');
        } else {
            if (!grunt.file.exists('embuild/CMakeCache.txt')) {
                grunt.file.mkdir('embuild');
                grunt.task.run('shell:emscripten_cmake');
                grunt.task.run('shell:emscripten_cmake');
            }
            grunt.task.run('shell:emscripten_make');
            grunt.task.run('bowercopy:html');
            if (grunt.option('jsMin')) {
                grunt.task.run('uglify');
            } else {
                grunt.task.run('bowercopy:js');
            }
        }
        grunt.task.run('bowercopy:server');
    });
    grunt.registerTask('init', ['update_submodules']);
}
