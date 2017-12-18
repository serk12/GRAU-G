#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 V;
uniform mat4 modelViewMatrix;

void main()
{

    fragColor = frontColor*normalize(cross(dFdx(V),dFdy(V))).z;
}
