#include "DynamicCreature.h"

DynamicCreature::DynamicCreature(TexturedModel& _model, const std::string& _name, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	Dynamic(_model, _position, _rotation, _scale),
	name(_name),
	knockbackTimer(0.0f),
	attackTimer(0.0f),
	health(100.0f),
	maxHealth(health)
{
	isAttackable = true;
}

DynamicCreature::~DynamicCreature()
{
}

void DynamicCreature::behaviour(float deltaTime, Dynamic& player)
{
}

void DynamicCreature::update(float deltaTime, Dynamic& player)
{
	if (knockbackTimer > 0.0f)
	{
		velocity = knockbackVelocity * 10.0f;
		isAttackable = false;
		knockbackTimer -= deltaTime;
		if (knockbackTimer <= 0.0f)
		{
			attackTimer = 0.0f;
			controllable = true;
			isAttackable = true;
		}
	}
	else
	{
		if (health <= 0)
			alive = false;

		behaviour(deltaTime, player);
	}
}
