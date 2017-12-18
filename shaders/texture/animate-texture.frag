#version 330 core

in vec2 vtexCoord;
in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float speed = 0.1;
uniform float time;

void main()
{
    fragColor = frontColor * texture(colorMap,  vec2(vtexCoord.x+speed*time,vtexCoord.y+speed*time));
}
