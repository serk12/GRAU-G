#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float n=4;
uniform vec4 lightPosition;
uniform mat4 modelViewMatrixInverse;  

void main()
{
    frontColor = vec4(1.0,1.0,1.0,1.0) *  vec4(normalize(normalMatrix * normal).z);
    vec4  F = modelViewMatrixInverse * lightPosition;
    float d = distance(vertex,F.xyz);
    float w = clamp(1/pow(d,n),0,1);
    vec3  V = (1.0-w)*vertex + w*(F.xyz);
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}
