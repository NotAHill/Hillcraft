#version 330 core

out vec4 outColour;
in vec3 passColour;

void main()
{
	outColour = vec4(passColour, 1.0);
}