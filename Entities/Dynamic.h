#pragma once
#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "Object.h"

#include <string>

class Terrain;

class Dynamic : public Object
{
public:
	Dynamic(TexturedModel& _model, glm::vec3 _position = { 0, 0, 0 }, glm::vec3 _rotation = { 0, 0, 0 }, float _scale = 1.0f);
	virtual ~Dynamic();

	virtual void update(float deltaTime, Dynamic& player) = 0;
	virtual void onInteract(Dynamic& player) = 0;
	virtual float getCurrentHeight(const Terrain& terrain) = 0;
	
public:
	glm::vec3 velocity = { 0,0,0 };
	
	// Each entity has these attributes
	bool isAttackable = false;
	bool isFriendly = true;
	int baseDamage;
};

#endif // !DYNAMIC_H



