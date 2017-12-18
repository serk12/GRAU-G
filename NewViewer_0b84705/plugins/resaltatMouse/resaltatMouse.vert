#version 330 core

layout (location=0) in vec3 vertex;
layout (location=2) in vec3 color;

uniform mat4 modelViewProjectionMatrix;
uniform vec4 colorSelect;

out vec4 vFrontColor;

void main() {
  vFrontColor = colorSelect;
  gl_Position = modelViewProjectionMatrix*vec4(vertex,1);
}


