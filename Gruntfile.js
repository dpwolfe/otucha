module.exports = function (grunt) {
	var path = require('path');
    require('load-grunt-tasks')(grunt);
    grunt.loadNpmTasks('grunt-bowercopy');
    grunt.loadNpmTasks('grunt-contrib-uglify');

    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        shell: {
            options: {
                stderr: false
            },
            target: {
                command: 'echo Use build:emscripten or build:native'
            },
            native: {
                command: [
                    'echo Building native',
                    'cd build',
                    'cmake -DOTUCHA_EMSCRIPTEN_ENABLED=OFF -DOTUCHA_DO_NOT_WARN_GL_H=ON ..'
                ].join('&&')
            },
            coveralls: {
                command: [
                    'echo Building coveralls',
                    'cd cbuild',
                    'cmake -DOTUCHA_EMSCRIPTEN_ENABLED=OFF -DOTUCHA_DO_NOT_WARN_GL_H=ON -DCOVERALLS=ON -DCMAKE_BUILD_TYPE=Debug ..'
                ].join('&&')
            },
            xcode: {
                command: [
                    'echo Building Xcode',
                    'cd xbuild',
                    'cmake -DOTUCHA_EMSCRIPTEN_ENABLED=OFF -DOTUCHA_DO_NOT_WARN_GL_H=ON -G Xcode ..',
                    'open -a Xcode otucha.xcodeproj'
                ].join('&&')
            },
            submodule_init: {
                command: [
                    'echo Initializing glfw submodule',
                    'cd ' + path.join('submodules', 'glfw'),
                    'git submodule init',
                    'git submodule update'
                ].join('&&')
            },
            emscripten_cmake: {
                options: {
                    failOnError: false
                },
                command: [
                    'cd embuild',
                    'emcmake cmake ..'
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
                    srcPrefix: 'src',
                    destPrefix: 'www'
                },
                files: {
                    'server.js': 'server.js'
                }
            },
            html: {
                options: {
                    srcPrefix: 'embuild',
                    destPrefix: 'www'
                },
                files: {
                    'index.html': 'otucha.html'
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
            },
            dist: {
                options: {
                    srcPrefix: 'dist',
                    destPrefix: 'www'
                },
                files: {
                    'otucha.js': 'otucha.js',
                    'index.html': 'index.html'
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

    grunt.registerTask('default', function () {
        grunt.task.run(['build']);
    });
    grunt.registerTask('build', ['build:native']);
    grunt.registerTask('build:native', function () {
        grunt.file.mkdir('build');
        grunt.task.run(['shell:native']);
    });
    grunt.registerTask('build:coveralls', function () {
        grunt.file.mkdir('cbuild');
        grunt.task.run(['shell:coveralls']);
    });
    grunt.registerTask('build:xcode', function () {
        grunt.file.mkdir('xbuild');
        grunt.task.run(['shell:xcode']);
    });
    grunt.registerTask('build:js', function () {
        if (grunt.option('jsUseDist')) {
            grunt.task.run(['bowercopy:dist']);
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
    grunt.registerTask('init', function () {
        grunt.task.run('shell:submodule_init');
    });
}
