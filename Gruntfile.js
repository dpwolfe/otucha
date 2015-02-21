module.exports = function (grunt) {
    require('load-grunt-tasks')(grunt);

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
                        'echo Building native'
                    ].join('&&')
                }
            }
    });

    grunt.registerTask('build', ['build:native']);
    grunt.registerTask('build:native', ['shell:native']);
    grunt.registerTask('default', function () {
        grunt.log.writeln('Running "default" task.');
        grunt.task.run(['build']);
    });
}