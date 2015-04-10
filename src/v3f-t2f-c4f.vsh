#version 100

#ifdef GL_ES
precision highp float;
#endif

uniform mat4 mc_ec;
uniform mat4 ec_dc;

attribute vec3 mcPosition;
attribute vec2 texCoord;
attribute vec4 color;

void main()
{
	gl_TexCoord[0].xy = texCoord.xy;
	gl_FrontColor     = color;
	gl_Position       = ec_dc * (mc_ec * vec4(mcPosition, 1.0));
}