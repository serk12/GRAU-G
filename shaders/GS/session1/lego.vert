#version 330 core

in vec3 vertex;
in vec3 gNormal;
in vec3 gfrontColor;
in vec2 gTexCoord;
in int gtop;

out vec4 vfrontColor;

uniform sampler2D colorMap;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
	vec4 TC=texture(colorMap, gTexCoord); 
	if (gNormal.x == 0)
		vfrontColor=vec4(0);
    else 
		vfrontColor = vec4(gfrontColor,1.0);
    gl_Position =  vec4(vertex, 1.0);
}
   
