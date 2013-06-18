#version 330
#define POSITION 	0

layout (location = POSITION)  in vec3 position;
uniform mat4 modelViewProjectionMatrix;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}
