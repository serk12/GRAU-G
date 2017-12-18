#version 330 core

uniform mat3 normalMatrix;

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
    vec3 L = normalize(lightPosition.xyz - P.xyz);
    vec3 V = normalize(2.0*max(0.0,dot(N,L))*N-L);
    
    vec3 R = normalize(-P);
    
    fragColor = matAmbient*lightAmbient + matDiffuse*lightDiffuse*max(0.0,dot(N,L)) + matSpecular*lightSpecular*pow(max(0.0,dot(R,V)),matShininess);
}
