#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform float time;
uniform float scale;
const float PI = 3.14159;

float triangleWave(float x) {
	return abs(mod(x,2) - 1.0);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color, 1.0)*N.z;
 
    gl_Position = modelViewProjectionMatrix * vec4(normalize(vertex), 1.0);
}
