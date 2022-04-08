#pragma once

#include "glm.h"

struct CollisionBox
{
	glm::vec3 position;
	float radius;

	CollisionBox(const float& _radius) : radius(_radius) {}
	bool isPointInBox(const glm::vec3& point);
	void update(const glm::vec3& _pos) { position = _pos; }
};

