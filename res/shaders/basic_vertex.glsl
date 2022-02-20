#version 330 core

// Receive Vertex Coords at location 0
layout (location = 0) in vec3 inVertexPosition;

// Receive Colour Values at location 1
layout (location = 1) in vec3 inColour;

// Output the colour to the fragment shader
out vec3 passColour;

// Matrices
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	// Multiply in reverse (as matrix multiplication is back to front)
	gl_Position = projection * view * model * vec4(inVertexPosition, 1.0);

	passColour = inColour;
}