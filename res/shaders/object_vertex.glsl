#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in vec3 inNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 passTextureCoords;
out vec3 passNormal;
out vec3 passFragPos;

void main()
{
	passFragPos = vec3(model * vec4(inVertexPosition, 1.0));
	passNormal = mat3(transpose(inverse(model))) * inNormal;
	passTextureCoods = inTextureCoods;

	gl_Position = projection * view * vec4(passFragPos, 1.0);
}