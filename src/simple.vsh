#version 100

#ifdef GL_ES
precision highp float;
#endif

uniform mat4 mc_ec;
uniform mat4 ec_dc;
uniform mat3 normal_mat;
uniform vec3 kd;

const vec3 lightSourceDir = vec3(1.0, 1.0, 1.0);

attribute vec3 mcPosition;
attribute vec3 mcNormal;

varying vec3 colorToFS;

vec3 evaluateLightingModel(in vec3 ec_q, in vec3 ec_nHat)
{
	float factor = dot(normalize(lightSourceDir), ec_nHat);
	if (factor < 0.0)
	{
		factor = 0.0;
	}
	return factor * kd;
}

void main()
{
	vec4 p_ecPosition = mc_ec * vec4(mcPosition, 1.0);
	vec3 ec_nHat = normalize(normal_mat * mcNormal);
	colorToFS = evaluateLightingModel(p_ecPosition.xyz, ec_nHat);
	gl_Position = ec_dc * p_ecPosition;
}
