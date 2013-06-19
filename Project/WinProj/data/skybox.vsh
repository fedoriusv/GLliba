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

uniform Transform 	transform;

void main()
{
	mat4 skypos = transform.modelMatrix;
	skypos[3].xyz = transform.viewPosition;
		
	vec4 viewProjectionModelMatrix = transform.viewProjectionMatrix * skypos * vec4(position, 1.0);
	gl_Position = viewProjectionModelMatrix.xyww;
}
