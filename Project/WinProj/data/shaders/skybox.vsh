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

uniform Transform 	transform;

out vec2 TexCoord;

void main()
{
	TexCoord = texCoord0;
	
	mat4 skypos = transform.modelMatrix;
	skypos[3].xyz = transform.viewPosition;
		
	vec4 vertex = skypos * vec4(position, 1.0);
	gl_Position = transform.projectionMatrix * transform.viewMatrix * vertex;
}
