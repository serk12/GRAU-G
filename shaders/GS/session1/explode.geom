#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vNormal[];

uniform float time;
const float speed = 1.2;

uniform mat4 modelViewProjectionMatrix;


void main( void )
{
	vec3 mit = vec3(0,0,0);
	for(int i = 0; i < 3; ++i){
		mit += vNormal[i];
	}
	mit /= 3.0;
	vec3 desp = mit*(speed*mod(time, 5));
	for( int i = 0 ; i < 3 ; ++i)
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*(gl_in[i].gl_Position+vec4(desp,1.0));
		EmitVertex();
	}
    EndPrimitive();
}
