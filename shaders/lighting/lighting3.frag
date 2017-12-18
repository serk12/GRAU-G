#version 330 core

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec3 NV, P;
out vec4 fragColor;

void main()
{
    vec3 N = normalize(normalMatrix*NV);
    vec3 L = normalize(lightPosition.xyz - P);
    vec3 H = normalize(vec3(0.0,0.0,1.0) + L);
    fragColor = matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0,dot(N,H)),matShininess);
}
