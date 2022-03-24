#version 330 core

in vec3 textureCoords;
out vec4 outColour;

uniform samplerCube cubeMap;
uniform vec3 skyColour;

const float upper = 30.0;
const float lower = 0.0;

const float levels = 5.0;

void main()
{
	//outColour = texture(cubeMap, textureCoords);
	vec4 textureColour = texture(cubeMap, textureCoords);
	
	// Cel shading
	float sum = (textureColour.r + textureColour.g + textureColour.b) / 3.0;
	sum = floor(sum * levels) / levels;
	textureColour.rgb = sum * skyColour;
	
	float factor = (textureCoords.y - lower) / (upper - lower);
	factor = clamp(factor, 0.0, 1.0);
	outColour = mix(vec4(skyColour, 1.0), textureColour, factor);
}
// rgba, rbga, brga, bgra, gbra, grba