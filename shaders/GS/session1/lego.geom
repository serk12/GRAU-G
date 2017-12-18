#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];

out vec3 gNormal;
out vec4 gfrontColor;
out int gTop;

out vec2 gTexCoord;

uniform float step = 0.2;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void printVert(vec3 V, vec3 bar, float N, int top){
	gNormal = vec3(0,0,0);
	N = 1;
	gTop = top;
	float dist0 = 	(bar.x - V.x)*(bar.x - V.x)+
					(bar.y - V.y)*(bar.y - V.y)+
					(bar.z - V.z)*(bar.z - V.z);
	float dist1 = 	(bar.x - V.x)*(bar.x - V.x)+
					(bar.y - V.y)*(bar.y - V.y)+
					(bar.z - V.z)*(bar.z - V.z);
	float dist2 = 	(bar.x - V.x)*(bar.x - V.x)+
					(bar.y - V.y)*(bar.y - V.y)+
					(bar.z - V.z)*(bar.z - V.z);
					
	int min = 0; float minDist = dist0;
	if(dist1 < minDist) {min = 1; minDist = dist1;}
	if(dist2 < minDist) {min = 2; minDist = dist2;}

	gfrontColor=vfrontColor[min]*N;
	gTexCoord=vec2(V.z, V.x); 
	gl_Position=modelViewProjectionMatrix*vec4(V, 1.0);
	EmitVertex();
}

void main( void )
{
	vec3 bar = vec3(0,0,0);
	for(int i = 0; i < 3; ++i){
		bar += gl_in[i].gl_Position.xyz;
	}
	bar /= (3.0*step);
	bar.x = trunc(bar.x);
	bar.y = trunc(bar.y);
	bar.z = trunc(bar.z);
	bar *= step;

	float halfStep = step/2.0;

	//front
	printVert(vec3(-halfStep,-halfStep,+halfStep)+bar, bar, 1.0, 0);
	printVert(vec3(+halfStep,-halfStep,+halfStep)+bar, bar, 1.0, 0);
	printVert(vec3(-halfStep,+halfStep,+halfStep)+bar, bar, 1.0, 0);
	printVert(vec3(+halfStep,+halfStep,+halfStep)+bar, bar, 1.0, 0);		
    EndPrimitive();

    //back
	printVert(vec3(-halfStep,+halfStep,-halfStep)+bar, bar, 0.1, 0);
	printVert(vec3(+halfStep,+halfStep,-halfStep)+bar, bar, 0.1, 0);
	printVert(vec3(-halfStep,-halfStep,-halfStep)+bar, bar, 0.1, 0);
	printVert(vec3(+halfStep,-halfStep,-halfStep)+bar, bar, 0.1, 0);		
    EndPrimitive();

    //left
	printVert(vec3(-halfStep,-halfStep,-halfStep)+bar, bar, 0.8, 0);
	printVert(vec3(-halfStep,-halfStep,+halfStep)+bar, bar, 0.8, 0);
	printVert(vec3(-halfStep,+halfStep,-halfStep)+bar, bar, 0.8, 0);
	printVert(vec3(-halfStep,+halfStep,+halfStep)+bar, bar, 0.8, 0);		
    EndPrimitive();

    //right
	printVert(vec3(+halfStep,+halfStep,-halfStep)+bar, bar, 0.2, 0);
	printVert(vec3(+halfStep,+halfStep,+halfStep)+bar, bar, 0.2, 0);
	printVert(vec3(+halfStep,-halfStep,-halfStep)+bar, bar, 0.2, 0);
	printVert(vec3(+halfStep,-halfStep,+halfStep)+bar, bar, 0.2, 0);		
    EndPrimitive();
    //top
	printVert(vec3(-halfStep,+halfStep,+halfStep)+bar, bar, 0.5, 1);
	printVert(vec3(+halfStep,+halfStep,+halfStep)+bar, bar, 0.5, 1);
	printVert(vec3(-halfStep,+halfStep,-halfStep)+bar, bar, 0.5, 1);
	printVert(vec3(+halfStep,+halfStep,-halfStep)+bar, bar, 0.5, 1);		
    EndPrimitive();

    //bottom
	printVert(vec3(+halfStep,-halfStep,-halfStep)+bar, bar, 0.4, 0);
	printVert(vec3(+halfStep,-halfStep,+halfStep)+bar, bar, 0.4, 0);
	printVert(vec3(-halfStep,-halfStep,-halfStep)+bar, bar, 0.4, 0);
	printVert(vec3(-halfStep,-halfStep,+halfStep)+bar, bar, 0.4, 0);		
    EndPrimitive();

}
