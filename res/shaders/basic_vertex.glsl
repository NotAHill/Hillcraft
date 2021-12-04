#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inColour;

out vec3 passColour;

void main()
{
	gl_Position = vec4(inVertexPosition, 1.0);

	passColour = inColour;
}