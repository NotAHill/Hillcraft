#version 330 core

out vec4 outColour;
flat in vec3 passColour;

// Phong Shading
struct Light
{
	vec3 direction;	
	vec3 bias;
	vec3 colour;
};

flat in vec3 passNormal;
in vec3 passFragPos;

uniform vec3 cameraPos;
uniform Light light;

vec3 calculateLighting()
{
	vec3 normal = normalize(passNormal);
	float brightness = max(dot(-light.direction, normal), 0.0);

	vec3 viewDir = normalize(cameraPos - passFragPos);
	vec3 reflectDir = reflect(light.direction, normal);
	float shininess = pow(max(dot(viewDir, reflectDir), 0.0), 32);

	return (light.colour * light.bias.x) + (brightness * light.colour * light.bias.y) + (shininess * light.colour * light.bias.z);
}

void main()
{
	vec3 lighting = calculateLighting();
	outColour = vec4(passColour * lighting, 1.0);
}

// Gouraud Shading
//void main()
//{
//	outColour = vec4(passColour, 1.0);
//}