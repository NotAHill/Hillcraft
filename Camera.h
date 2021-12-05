#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();

	void update();
	void hookEntity(const Entity& _entity);

	const Matrix4& getViewMatrix() const;
	const Matrix4& getProjectionMatrix() const;
	const Matrix4& getProjectionViewMatrix() const;

private:
	const Entity* entity;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 projViewMatrix;

	Vector3 front, up, right, worldUp;

	float yaw, pitch;
};



#endif // !CAMERA_H
