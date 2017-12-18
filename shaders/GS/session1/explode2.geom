#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vNormal[];

uniform float time;
const float speed = 1.2;
const float angSpeed = 8.0;

uniform mat4 modelViewProjectionMatrix;


void main( void )
{
	vec3 mit = vec3(0,0,0);
	vec3 bar = vec3(0,0,0);
	for(int i = 0; i < 3; ++i){
		mit += vNormal[i];
		bar += gl_in[i].gl_Position.xyz;
	}
	mit /= 3.0;
	bar /= 3.0;

	vec3 desp = mit*(speed*mod(time, 3));
	float rot  = angSpeed*time;
	mat4 Rz = mat4(
		vec4(cos(rot), -sin(rot), 0,0), 
		vec4(sin(rot), cos(rot), 0,0), 
		vec4(0, 0, 1,0),
		vec4(0, 0, 0,1)
	);

	for( int i = 0 ; i < 3 ; ++i)
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*(Rz*(gl_in[i].gl_Position-vec4(bar,1.0))+vec4(desp,1.0));
		EmitVertex();
	}
    EndPrimitive();
}
