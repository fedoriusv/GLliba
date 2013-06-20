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
    mat4 viewProjectionMatrix;
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
	
	vec3 reflection;
};

out Vertex fragVertex;

void main()
{
	vec4 vertex   = transform.modelMatrix * vec4(position, 1.0);
	vec4 lightDir = light0.position - vertex;
	vec4 vNormal  = transform.normalMatrix * vec4(normal, 0.0);
	
	fragVertex.normal 		= vNormal.xyz; 
	fragVertex.texCoord0 	= texCoord0;
	fragVertex.lightDir 	= vec3(lightDir);
	fragVertex.viewDir  	= transform.viewPosition - vec3(vertex);
	fragVertex.distance 	= length(lightDir);
	
	fragVertex.reflection   = reflect(vertex.xyz - transform.viewPosition, normalize(vNormal.xyz));

	gl_Position = transform.viewProjectionMatrix * vertex;
}
