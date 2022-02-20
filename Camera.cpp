#include "Camera.h"

Camera::Camera()
{
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)1280 / (float)640, 0.1f, 100.0f);
	position = { 0, 0, -3.5f };
}

void Camera::update()
{
	position = entity->position;
	rotation = entity->rotation;

	//might not work
	//viewMatrix = glm::lookAt(position, position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	viewMatrix = glm::translate(matrix, position);
}

void Camera::hookEntity(const Entity& _entity)
{
	entity = &_entity;
}

const glm::mat4 Camera::getViewMatrix() const
{
	return viewMatrix;
}

const glm::mat4 Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}
