#version 330 core

layout (location = 0) in vec3 inVertexPosition;
layout (location = 1) in vec3 inColour;
layout (location = 2) in vec3 inNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 passColour;
out float visibility;

// Phong Shading
out vec3 passNormal;
out vec3 passFragPos;

uniform float density;
uniform float gradient;

void main()
{
	passFragPos = vec3(model * vec4(inVertexPosition, 1.0));
	passNormal = mat3(transpose(inverse(model))) * inNormal;
	passColour = inColour;

	vec4 positionFromCamera = view * vec4(passFragPos, 1.0);
	gl_Position = projection * positionFromCamera;

	// Fog calculation
	float distanceFromCamera = length(positionFromCamera.xyz);
	visibility = exp(-pow((distanceFromCamera * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}

// Gouraud Shading
//struct Light
//{
//	vec3 direction;	
//	vec3 bias;
//	vec3 colour;
//};
//
//uniform Light light;
//uniform vec3 cameraPos;
//
//vec3 calculateLighting()
//{
//	vec3 normal = normalize(inNormal);
//	float brightness = max(dot(-light.direction, normal), 0.0);
//
//	vec3 viewDir = normalize(cameraPos - inVertexPosition);
//	vec3 reflectDir = reflect(light.direction, normal);
//	float shininess = pow(max(dot(viewDir, reflectDir), 0.0), 64);
//
//	return (light.colour * light.bias.x) + (brightness * light.colour * light.bias.y) + (shininess * light.colour * light.bias.z);
//}
//
//void main()
//{
//	gl_Position = projection * view * model * vec4(inVertexPosition, 1.0);
//
//	vec3 lighting = calculateLighting();
//	passColour = inColour * lighting;
//}