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
                        'echo Building native',
                        'cd build',
                        'cmake -DOTUCHA_EMSCRIPTEN_ENABLED=OFF ../src'
                    ].join('&&')
                }
            }
    });

    grunt.registerTask('build', ['build:native']);
    grunt.registerTask('build:native', function () {
        grunt.file.mkdir('build');
        grunt.task.run(['shell:native']);
    });
    grunt.registerTask('default', function () {
        grunt.log.writeln('Running "default" task.');
        grunt.task.run(['build']);
    });
}