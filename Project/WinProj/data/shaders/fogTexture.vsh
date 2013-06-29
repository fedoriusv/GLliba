#version 330

#define POSITION 	0
#define NORMAL 		2
#define TEXCOORD0 	5

layout (location = POSITION)  in vec3 position;
layout (location = NORMAL)    in vec3 normal;
layout (location = TEXCOORD0) in vec2 texCoord0;

struct Transform
{
	mat4 modelMatrix;
	mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 normalMatrix;
    vec3 viewPosition;
};

struct Light0
{
	vec4 	position;
    vec4 	ambient;
    vec4 	diffuse;
    vec4 	specular;
    vec3 	attenuation;
};

uniform Transform 	transform;
uniform Light0 		light0;

struct Vertex 
{
    vec2  texCoord0;
    vec3  normal;
    vec3  lightDir;
    vec3  viewDir;
    float distance;
	vec4  viewPos;
};

smooth out Vertex fragVertex;

void main()
{
	vec4 vertex   = transform.modelMatrix * transform.viewMatrix * vec4(position, 1.0);
	gl_Position = transform.projectionMatrix * vertex;
	
	vec4 vNormal  = transform.normalMatrix * vec4(normal, 0.0);
	
	fragVertex.normal 		= vNormal.xyz; 
	fragVertex.texCoord0 	= texCoord0;
	fragVertex.viewPos		= vertex;
}
