#pragma once
#ifndef LIGHT_H

#include "../Maths/glm.h"

class Light
{
public:
	Light(glm::vec3 _position, glm::vec3 _direction, glm::vec3 _colour, glm::vec3 _bias);

	const glm::vec3& getColour();
	const glm::vec3& getDirection();
	const glm::vec3& getBias();
	const glm::vec3& getPosition();

	glm::vec3 colour;
	glm::vec3 direction;
	glm::vec3 bias;
	glm::vec3 position;
};


#endif // !LIGHT_H
