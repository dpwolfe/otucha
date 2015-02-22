module.exports = function (grunt) {
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
                    'cmake -DOTUCHA_EMSCRIPTEN_ENABLED=OFF ../src'
                ].join('&&')
            },
            emscripten_step1: {
                options: {
                    failOnError: false
                },
                command: [
                    'echo Building JavaScript',
                    'cd embuild',
                    'emcmake cmake ../src'
                ].join('&&')
            },
            emscripten_step2: {
                command: [
                    'cd embuild',
                    'emcmake cmake ../src',
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
            app: {
                options: {
                    srcPrefix: 'embuild',
                    destPrefix: 'www'
                },
                files: {
                    'otucha-full.js': 'otucha.js',
                    'index.html': 'otucha.html'
                }
            }
        },
        uglify: {
            options: {
                sourceMap: false,
                banner: '/*! <%= pkg.name %> <%= grunt.template.today("yyy-mm-dd-HH-MM-ss") %> */\n',
                compress: true,
                mangle: false
            },
            build: {
                files: {
                    'www/otucha.js': [
                        'www/otucha-full.js'
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
    grunt.registerTask('build:js', function () {
        grunt.file.mkdir('embuild');
        grunt.task.run(['shell:emscripten_step1']);
        grunt.task.run(['shell:emscripten_step2']);
        grunt.task.run(['bowercopy', 'uglify']);
    })
}