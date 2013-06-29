#version 330
#define POSITION 	0

layout (location = POSITION)  in vec3 position;

struct Transform
{
	mat4 modelMatrix;
	mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 normalMatrix;
    vec3 viewPosition;
};

uniform Transform transform;

void main()
{
	vec4 vertex = transform.modelMatrix * vec4(position, 1.0);
	gl_Position = transform.projectionMatrix * transform.viewMatrix * vertex;
}