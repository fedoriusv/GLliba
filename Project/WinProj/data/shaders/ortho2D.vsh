#version 330

#define POSITION 	0
#define TEXCOORD0 	5

struct Transform
{
	mat4 modelMatrix;
	mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 normalMatrix;
    vec3 viewPosition;
	mat4 orthoMatrix;
};
uniform Transform transform;

layout (location = POSITION) 	in vec3 position;
layout (location = TEXCOORD0) 	in vec2 texCoord0;

out vec2 TexCoord;

void main()
{
	vec4 vertex   = transform.modelMatrix * vec4(position.xy, 0.0 , 1.0);
	gl_Position = transform.orthoMatrix * vertex;
	
	TexCoord = texCoord0;
}