#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float step = 0.5;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void printVert(vec3 V, float N){
	gfrontColor=vec4(vec3(0.8), 1)*N;
	gl_Position=modelViewProjectionMatrix*vec4(V, 1.0);
	EmitVertex();
}

void main( void )
{
	vec3 bar = vec3(0,0,0);
	for(int i = 0; i < 3; ++i){
		bar += gl_in[i].gl_Position.xyz;
	}
	bar /= 3.0;
	bar /= step;
	bar.x = trunc(bar.x);
	bar.y = trunc(bar.y);
	bar.z = trunc(bar.z);
	bar *= step;
	//front +
	printVert(vec3(-step,-step,+step)+bar, 1.0);
	printVert(vec3(+step,-step,+step)+bar, 1.0);
	printVert(vec3(-step,+step,+step)+bar, 1.0);
	printVert(vec3(+step,+step,+step)+bar, 1.0);		
    EndPrimitive();

    //back +
	printVert(vec3(-step,+step,-step)+bar, 0.1);
	printVert(vec3(+step,+step,-step)+bar, 0.1);
	printVert(vec3(-step,-step,-step)+bar, 0.1);
	printVert(vec3(+step,-step,-step)+bar, 0.1);		
    EndPrimitive();

    //left
	printVert(vec3(-step,-step,-step)+bar, 0.8);
	printVert(vec3(-step,-step,+step)+bar, 0.8);
	printVert(vec3(-step,+step,-step)+bar, 0.8);
	printVert(vec3(-step,+step,+step)+bar, 0.8);		
    EndPrimitive();

    //right
	printVert(vec3(+step,+step,-step)+bar, 0.2);
	printVert(vec3(+step,+step,+step)+bar, 0.2);
	printVert(vec3(+step,-step,-step)+bar, 0.2);
	printVert(vec3(+step,-step,+step)+bar, 0.2);		
    EndPrimitive();

    //top
	printVert(vec3(-step,+step,+step)+bar, 0.5);
	printVert(vec3(+step,+step,+step)+bar, 0.5);
	printVert(vec3(-step,+step,-step)+bar, 0.5);
	printVert(vec3(+step,+step,-step)+bar, 0.5);		
    EndPrimitive();

    //bottom
	printVert(vec3(+step,-step,-step)+bar, 0);
	printVert(vec3(+step,-step,+step)+bar, 0);
	printVert(vec3(-step,-step,-step)+bar, 0);
	printVert(vec3(-step,-step,+step)+bar, 0);		
    EndPrimitive();

}
