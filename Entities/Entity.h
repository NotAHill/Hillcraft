#pragma once
#ifndef ENTITY_H
#define ENTITY_H

// Temporary
#include <glm/glm.hpp>

class Entity
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	float scale = 1.0f;
};

#endif // !ENTITY_H


