#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inColour;
layout (location = 2) in vec3 inNormal;

flat out vec3 passColour;
out vec3 passNormal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	fragPos = vec3(model * vec4(inVertexPosition, 1.0));

	passNormal = mat3(transpose(inverse(model))) * inNormal;
	gl_Position = projection * view * model * vec4(inVertexPosition, 1.0);

	passColour = inColour;
}