#version 330 core

in vec4 frontColor;
out vec4 fragColor;
uniform int n;

void main()
{
    if (mod(gl_FragCoord.y,n) != 0.5) discard;
    fragColor = frontColor;
}
