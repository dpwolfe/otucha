#version 100

#ifdef GL_ES
precision highp float;
#endif

varying vec3 colorToFS;

void main()
{
	gl_FragColor = vec4(colorToFS, 1.0);
}