#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "glm.h"

#include "../Entity.h"
#include "../Camera.h"

//class Entity;
//class Camera;
//
//Matrix4 makeModelMatrix(const Entity& entity);
//Matrix4 makeViewMatrix(const Camera& camra);
//Matrix4 makeProjectionMatrix(float fov);

namespace
{
	template<typename Type>
	inline Matrix4 makeMatrix(const Type& param)
	{
		Matrix4 matrix;

		matrix = glm::rotate(matrix, glm::radians(param.rotation.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(param.rotation.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(param.rotation.z), { 0, 0, 1 });

		matrix = glm::translate(matrix, param.position);

		return matrix;
	}
}

constexpr auto makeModelMatrix = makeMatrix<Entity>;
constexpr auto makeViewMatrix = makeMatrix<Camera>;

inline Matrix4 makeProjectionMatrix(float fov)
{
	// Add a config class
	return glm::perspective(glm::radians(fov), 1280.0f / 640.0f, 0.1f, 1000.0f);
}



#endif

