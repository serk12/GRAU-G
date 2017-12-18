#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
    float s = mod(vtexCoord.s*8.0,8.0); s = mod(s,2.0);
    float t = mod(vtexCoord.t*8.0,8.0); t = mod(t,2.0);
    if((s < 1.0 && t < 1.0) || (s > 1.0 && t > 1.0)){
    	fragColor = vec4(0.7,0.7,0.7,1.0);	
    }
    else{
    	fragColor = vec4(0.0,0.0,0.0,0.0);
    }
}
