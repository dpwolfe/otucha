#version 100

#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D texture;

varying vec2 texCoordxy;
varying vec4 texColor;

void main()
{
	float a = texture2D(texture, texCoordxy).r;
	gl_FragColor = vec4(texColor.rgb, texColor.a * a);
}