#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;

uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;

//fong
vec4 light(vec3 N, vec3 V, vec3 L){
	N = normalize(N); //normal
	V = normalize(V); //viewer
	L = normalize(L); //light
	vec3 R = 2.0*(N*L)*N- L;
	float NdotL = max(0.40, dot(N,L));
	float HdotV = max(0.40, dot(R,V));
    float Idiff = NdotL;
    float Ispec = 1;
	if (NdotL > 0) Ispec = pow(HdotV, matShininess);
        return	matAmbient  * lightAmbient  +  //ka*Ia;
                matDiffuse  * lightDiffuse  * Idiff + //Kd*Id(N*L)
				matSpecular * lightSpecular * Ispec; //ks*Is(R*V)^s
}

void main()
{
    vec3 P = (modelViewMatrix * vec4(vertex.xyz, 1.0)).xyz; //Point looking
	vec3 N = (normalMatrix * normal); //normal
	vec3 V = -P; //from point looking to viewer
	vec3 L = (lightPosition.xyz - P); //vector from object to light
	frontColor = light(N, V, L); //color + shader
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0); //assign color
}

