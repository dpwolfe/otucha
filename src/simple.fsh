#version 100

#ifdef GL_ES
precision highp float;
#endif

varying vec3 ec_nHat;
varying vec3 ecPosition;

uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float m;
uniform float a;

const vec3 lightPos1 = vec3(0.3, 0.8, -1.5);
const vec3 lightPos2 = vec3(0.8, -0.5, -1.5);
const vec3 lightPos3 = vec3(-0.8, -0.3, -1.5);
const float la = 1.0;
const float li = 1.0;

vec3 viewDir;

void modelLight(in vec3 lightPos, out float lambertian, out float specular)
{
    vec3 lightDir = normalize(lightPos - ecPosition);
	vec3 reflectDir = reflect(-lightDir, ec_nHat);
	lambertian = max(dot(lightDir, ec_nHat), 0.0);
	specular = 0.0;
	if (lambertian > 0.0)
	{
		float specAngle = max(dot(reflectDir, viewDir), 0.0);
		specular = pow(specAngle, m);
	}
}

void main() {
    viewDir = normalize(-ecPosition);

	float lambertian, specular, lambertianSum, specularSum;

    modelLight(lightPos1, lambertianSum, specularSum);

	modelLight(lightPos2, lambertian, specular);
	lambertianSum += lambertian;
	specularSum += specular;

	modelLight(lightPos3, lambertian, specular);
	lambertianSum += lambertian;
	specularSum += specular;

    gl_FragColor = vec4(ka*la + li*(kd*lambertianSum + ks*specularSum), a);
}
