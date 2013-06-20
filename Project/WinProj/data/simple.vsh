#version 330
#define POSITION 	0

layout (location = POSITION)  in vec3 position;

struct Transform
{
	mat4 modelMatrix;
    mat4 viewProjectionMatrix;
    mat4 normalMatrix;
    vec3 viewPosition;
};

uniform Transform transform;

void main()
{
	gl_Position = transform.viewProjectionMatrix * transform.modelMatrix * vec4(position, 1.0);
}
