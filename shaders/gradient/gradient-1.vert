#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMax, boundingBoxMin;

const vec3[5] colors = vec3[](vec3(1,0,0),vec3(1,1,0),vec3(0,1,0),vec3(0,1,1),vec3(0,0,1)); 

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float mid = (vertex.y - boundingBoxMin.y)/(boundingBoxMax.y - boundingBoxMin.y);
    float colorPoint = mid*4;
    int index = int(floor(colorPoint));
    vec3 color = mix(colors[index],colors[index + 1], fract(colorPoint));
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
