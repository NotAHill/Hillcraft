#include "Light.h"

Light::Light(glm::vec3 _position, glm::vec3 _direction, glm::vec3 _colour, glm::vec3 _bias) : 
	position(_position),
	direction(glm::normalize(_direction)),
	colour(_colour),
	bias(_bias)
{}

const glm::vec3& Light::getColour()
{
	return colour;
}

const glm::vec3& Light::getDirection()
{
	return direction;
}

const glm::vec3& Light::getBias()
{
	return bias;
}

const glm::vec3& Light::getPosition()
{
	return position;
}

