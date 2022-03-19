#version 330 core

#define MAX_LIGHTS 4
const float LEVELS = 3.0;

out vec4 outColour;

// Phong Shading
struct Light
{
	vec3 direction;	
	vec3 bias;
	vec3 colour;
};

in vec3 passNormal;
in vec3 passFragPos;
in vec2 passTextureCoords;
in float visibility;

uniform sampler2D modelTexture;
uniform vec3 cameraPos;
uniform Light light[MAX_LIGHTS];
uniform vec3 skyColour;

vec3 calculateLighting()
{
	vec3 normal = normalize(passNormal);
	vec3 viewDir = normalize(cameraPos - passFragPos);
	vec3 totalLight = vec3(0.0);

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		// Diffuse
		vec3 lightDir = normalize(light[i].direction);
		float brightness = max(dot(-lightDir, normal), 0.0);

		// Cel Shading
		float level = floor(brightness * LEVELS);
		brightness = level / LEVELS;

		// Specular
		vec3 reflectDir = reflect(lightDir, normal);
		float shininess = pow(max(dot(viewDir, reflectDir), 0.0), 16);
		
		// Cel Shading
		level = floor(shininess * LEVELS);
		shininess = level / LEVELS;

		totalLight += (light[i].colour * light[i].bias.x) + (brightness * light[i].colour * light[i].bias.y) + (shininess * light[i].colour * light[i].bias.z);
	}

	return totalLight;
}

void main()
{
	vec3 lighting = calculateLighting();
	vec4 textureColour = texture(modelTexture, passTextureCoords);
	outColour = textureColour * vec4(lighting, 1.0);
	outColour = mix(vec4(skyColour, 1.0), outColour, visibility);
}