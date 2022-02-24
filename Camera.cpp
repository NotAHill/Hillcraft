#include "Camera.h"

#include "Matrix.h"

/*
rotation x = pitch
rotation y = yaw
rotation z = roll
*/

Camera::Camera()
{
	projectionMatrix = makeProjectionMatrix(45.0f);
	position = { 0, 0, -3.5f };
	rotation = { 0, 0, 0 };
}

void Camera::update()
{
	if (entity != nullptr)
	{
		position = entity->position;
		rotation = entity->rotation;
	}

	//might not work
	//viewMatrix = glm::lookAt(position, position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	//glm::mat4 matrix = glm::mat4(1.0f);

	//matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	//matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	//matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	viewMatrix = makeViewMatrix(*this);
}

void Camera::hookEntity(const Entity& _entity)
{
	entity = &_entity;
}

const glm::vec3& Camera::getPosition() const
{
	return position;
}

const glm::mat4 Camera::getViewMatrix() const
{
	return viewMatrix;
}

const glm::mat4 Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}
