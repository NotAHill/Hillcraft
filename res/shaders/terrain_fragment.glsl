#version 330 core

out vec4 outColour;

//struct Light
//{
//	vec3 direction;	
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//
//	vec3 colour;
//};
//
in vec3 passColour;
//in vec3 passNormal;
//in vec3 passFragPos;
//
//uniform vec3 viewPos;
//uniform Light light;
//
//void main()
//{
//	// ambient
//	vec3 ambient = light.ambient * light.colour;
//	
//	// diffuse 
//	vec3 norm = normalize(passNormal);
//	vec3 lightDir = normalize(-light.direction);
//	float diff = max(dot(norm, lightDir), 0.0);
//	vec3 diffuse = light.diffuse * diff * light.colour;
//	
//	// specular
//	vec3 viewDir = normalize(viewPos - passFragPos);
//	vec3 reflectDir = reflect(-lightDir, norm);  
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
//	vec3 specular = light.specular * spec * light.colour;  
//
//	vec3 result = (ambient + diffuse + specular) * passColour;
//	outColour = vec4(result, 1.0);
//}

void main()
{
	outColour = vec4(passColour, 1.0);
}