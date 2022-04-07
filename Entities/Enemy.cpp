#include "Enemy.h"

Enemy::Enemy(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	DynamicCreature(_model, "sphere", _position, _rotation, _scale)
{
	isFriendly = false;
	health = 100;
	maxHealth = 100;
	attackTimer = 2.0f;
	equippedWeapon = nullptr;
}


void Enemy::behaviour()
{
}

void Enemy::attack()
{
	if (equippedWeapon == nullptr)
		return;
}

void Enemy::update(float deltaTime, Dynamic& player)
{
	if (health <= 0)
	{
		velocity = glm::vec3(0.0f);
		isAttackable = false;
		alive = false;
		return;
	}

	glm::vec3 target = player.position - position;
	float distance = std::sqrtf(target.x * target.x + target.y * target.y + target.z * target.z);
	attackTimer -= deltaTime;

	if (attackTimer <= 0.0f)
	{
		if (distance < 6.0f)
		{
			velocity = (target / distance) * 2.0f;
			if (distance < 1.5f)
				attack();
		}
		else
		{
			velocity = glm::vec3(0.0f);
		}

		attackTimer += 1.0f;
	}
}
