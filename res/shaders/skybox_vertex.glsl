#version 330 core

layout (location = 0) in vec3 inVertexPosition;
out vec3 textureCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(inVertexPosition, 1.0);
	textureCoords = inVertexPosition;
}