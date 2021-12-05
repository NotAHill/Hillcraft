#include "Camera.h"

#include "Maths/Matrix.h"

Camera::Camera()
{
	projectionMatrix = makeProjectionMatrix(90.0f);
	position = { 0.0f, 0.0f, -3.5f };
	worldUp = { 0.0f, 1.0f, 0.0f };
	front = { 0.0f, 0.0f, -1.0f };
	yaw = -90.0f;
	pitch = 0.0f;
}

void Camera::update()
{
	if (entity != nullptr)
	{
		position = entity->position;
		rotation = entity->rotation;
	}

	Vector3 newFront;
	newFront.x = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	newFront.y = sinf(glm::radians(pitch));
	newFront.z = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	viewMatrix = glm::lookAt(position, position + front, up);

	//viewMatrix = makeViewMatrix(*this);
	projViewMatrix = projectionMatrix * viewMatrix;
}

void Camera::hookEntity(const Entity& _entity)
{
	entity = &_entity;
}

const Matrix4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Matrix4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const Matrix4& Camera::getProjectionViewMatrix() const
{
	return projViewMatrix;
}
