#version 100

#ifdef GL_ES
precision highp float;
#endif

uniform mat4 mc_ec;
uniform mat4 ec_dc;
uniform vec3 kd;
const vec3 lightSourceDir = vec3(1.0, 1.0, 1.0);

varying vec3 mcPosition;
varying vec3 mcNormal;
varying vec3 colorToFS;

vec3 evaluateLightingModel(in vec3 ec_q, in vec3 ec_nHat)
{
	float factor = abs(dot(normalize(lightSourceDir), ec_nHat));
	return factor * kd;
}

void main()
{
	vec4 p_ecPosition = mc_ec * vec4(mcPosition, 1.0);
	mat3 normalMatrix = transpose(inverse(mat3x3(mc_ec)));
	vec3 ec_nHat = normalize(normalMatrix * mcNormal);
	colorToFS = evaluateLightingModel(p_ecPosition.xyz, ec_nHat);
	gl_Position = ec_dc * p_ecPosition;
}