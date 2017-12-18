#version 330 core

in vec3 frontColor;
out vec4 fragColor;
in vec3 N;

void main()
{
    fragColor = vec4(frontColor,1.0) * normalize(N).z;
}
