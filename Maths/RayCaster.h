#pragma once

#include "glm.h"

class RayCaster
{
public:
	RayCaster(const glm::vec3& _position, const glm::vec3& _direction);

	void step(float scale);
	glm::vec3 getEnd() const;
	float getLength() const;

private:
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 direction;
};

