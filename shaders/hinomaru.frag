#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
float radi = 0.2;
    float d = length(vtexCoord - vec2(0.5,0.5));
if(d>step(radi,d))	
    fragColor = vec4(1,0,0,1);
else
	fragColor = vec4(1,1,1,1);
	
}
