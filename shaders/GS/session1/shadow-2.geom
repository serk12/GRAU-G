#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin, boundingBoxMax;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0,0,0,1);
		vec4 aux = gl_in[i].gl_Position;
		aux.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix*aux;
		EmitVertex();
	}
    EndPrimitive();

	if(gl_PrimitiveIDIn == 0)
	{
		float y = boundingBoxMin.y - 0.01;
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMin.x,y,boundingBoxMax.z,1.0);
		EmitVertex();
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMin.x,y,boundingBoxMin.z,1.0);
		EmitVertex();
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMax.x,y,boundingBoxMin.z,1.0);
		EmitVertex();
		EndPrimitive();
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMin.x,y,boundingBoxMax.z,1.0);
		EmitVertex();
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMax.x,y,boundingBoxMax.z,1.0);
		EmitVertex();
		gfrontColor = vec4(0,0,1,1);
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMax.x,y,boundingBoxMin.z,1.0);
		EmitVertex();
		EndPrimitive();

	}
}
