#version 330 core

// Receive Vertex Coords at location 0
layout (location = 0) in vec3 inVertexPosition;

// Receive Colour Values at location 1
layout (location = 1) in vec3 inColour;

// Output the colour to the fragment shader
out vec3 passColour;

// Variables for matrix calculations
uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);

	passColour = inColour;
}