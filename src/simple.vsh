#version 100

#ifdef GL_ES
precision highp float;
#endif

attribute vec3 mcPosition;
attribute vec3 mcNormal;

uniform mat4 mc_ec;
uniform mat4 ec_dc;
uniform mat3 normal_mat;

const vec3 lightSourceDir = vec3(1.0, 1.0, 1.0);

varying vec3 p_ecPosition_ndc;
varying vec3 ec_nHat;

void main()
{
	vec4 p_ecPosition = mc_ec * vec4(mcPosition, 1.0);
	p_ecPosition_ndc = vec3(p_ecPosition) / p_ecPosition.w;
	ec_nHat = normalize(normal_mat * mcNormal);
	gl_Position = ec_dc * p_ecPosition;
}