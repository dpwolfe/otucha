#version 100

#ifdef GL_ES
precision highp float;
#endif

varying vec3 ec_nHat;
varying vec3 ecPosition;

uniform vec3 kd;

const vec3 lightPos = vec3(1.0, 1.0, 1.0);
const vec3 ambientColor = vec3(0.0, 0.3, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main() {
    vec3 lightDir = normalize(lightPos - ecPosition);
    vec3 reflectDir = reflect(-lightDir, ec_nHat);
    vec3 viewDir = normalize(-ecPosition);

    float lambertian = max(dot(lightDir, ec_nHat), 0.0);
    float specular = 0.0;

    if(lambertian > 0.0) {
       float specAngle = max(dot(reflectDir, viewDir), 0.0);
       specular = pow(specAngle, 4.0);
    }

    gl_FragColor = vec4(ambientColor +
                      lambertian*kd +
                      specular*specColor, 1.0);
}
