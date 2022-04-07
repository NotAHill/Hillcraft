#pragma once
#ifndef DYNAMIC_CREATURE_H
#define DYNAMIC_CREATURE_H

#include "Dynamic.h"

class Weapon;

class DynamicCreature : public Dynamic
{
public:
	DynamicCreature(TexturedModel& _model, const std::string& _name, glm::vec3 _position = { 0, 0, 0 }, glm::vec3 _rotation = { 0, 0, 0 }, float _scale = 1.0f);
	virtual ~DynamicCreature();

	// Called when performing attack
	virtual void attack() = 0;

	// Behaviour for AI
	virtual void behaviour(float deltaTime, Dynamic& player);

	// Update call
	virtual void update(float deltaTime, Dynamic& player);

protected:
	glm::vec3 knockbackVelocity;
	float knockbackTimer;

	float attackTimer;
	bool alive = true;

	int health;
	int maxHealth;
	bool controllable;

	std::string name;
	Weapon* equippedWeapon = nullptr;
};


#endif // !DYNAMIC_CREATURE_H


