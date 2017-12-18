#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform bool classic;
uniform float time;
void main()
{
	float radi = 0.2;
		float d = length(vtexCoord - vec2(0.5,0.5));
	if(classic){

	if(d>step(radi,d))	
		fragColor = vec4(1,0,0,1);
	else
		fragColor = vec4(1,1,1,1);
	}
	else{
		vec2 u = vec2(vtexCoord - vec2(0.5,0.5));
		float angle = atan(u.t,u.s)+time;
		if(mod(angle/(3.14159265/16)+0.5,2)<1)
			fragColor=vec4(1,0,0.5,1);
		else
			fragColor=vec4(0,1,1,1);
		if(d>step(radi,d))	
		fragColor = vec4(1,0,0.5,1);
	}
}
