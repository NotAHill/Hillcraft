#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

// Temporary
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Entity
{
public:
	Camera();

	void update();
	void hookEntity(const Entity& _entity);

	const glm::mat4 getViewMatrix() const;
	const glm::mat4 getProjectionMatrix() const;

	//glm::vec3 front;
	//glm::vec3 up;
	//glm::vec3 right;
	//glm::vec3 worldUp;
private:
	const Entity* entity;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};


#endif // !CAMERA_H

