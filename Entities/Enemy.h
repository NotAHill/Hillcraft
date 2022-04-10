#pragma once

#include "Object.h"

class Player;

class Enemy : public Object
{
public:
	Enemy(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale);

	void update(const float& deltaTime, Player& player);
	void receiveKnockback(const glm::vec3& knockback, const float& distance);

	int currentHealth;
	bool isAttackable;
	bool isAlive;
	int baseDamage;

private:
	glm::vec3 velocity;
	glm::vec3 knockbackVelocity;
	float knockbackTimer;
	int maxHealth;
	float attackTimer;
	
};

