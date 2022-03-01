#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera;
class Entity;

#include "../Entities/Camera.h"
#include "../Entities/Entity.h"

#include "../Config.h"

inline glm::mat4 makeModelMatrix(const Entity& entity)
{
	glm::mat4 matrix(1.0f);

	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, entity.position);

	return matrix;
}

inline glm::mat4 makeViewMatrix(const Camera& camera)
{
	glm::mat4 matrix(1.0f);

	matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -camera.position);

	return matrix;
}

inline glm::mat4 makeProjectionMatrix(float fov)
{
	return glm::perspective(glm::radians(fov), Config::ASPECT_RATIO, Config::NEAR, Config::FAR);
}

inline float barycentricInterpolation(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

#endif // !MATRIX_H

