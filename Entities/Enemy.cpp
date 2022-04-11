#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	Object(_model, _position, _rotation, _scale)
{
	velocity = { 0, 0, 0 };
	isAttackable = true;

	// Set knockback off
	knockbackTimer = -1.0f;
	attackTimer = 0.0f;
	knockbackVelocity = { 0, 0, 0 };

	currentHealth = 30;
	maxHealth = 30;
	baseDamage = 10 + rand() % 5;
	isAlive = true;
}

void Enemy::update(const float& deltaTime, Player& player)
{
	attackTimer += deltaTime;

	if (currentHealth <= 0)
	{
		velocity = glm::vec3(0.0f);
		isAttackable = false;
		isAlive = false;
		return;
	}

	// If it has received knockback then move back
	if (knockbackTimer > 0.0f)
	{
		velocity = knockbackVelocity * 10.0f;
		isAttackable = false;
		knockbackTimer -= deltaTime;
		knockbackVelocity *= 0.95f;
		if (knockbackTimer <= 0.0f)
		{
			isAttackable = true;
		}
	}
	// Otherwise target the player
	else
	{
		glm::vec3 target = player.position - position;
		float distance = glm::length(target);

		// Enemy will move if it is in player's range
		if (distance > 40.0f) velocity = glm::vec3(0.0f);
		else
		{
			// Unit target vector	     // speed
			velocity = (target / distance) * 5.0f;

			// Attack
			if (distance <= 6.0f && attackTimer >= 3.0f)
			{
				auto knockbackDir = glm::normalize(player.position - position);
				if (player.isAttackable)
				{
					player.receiveKnockback(knockbackDir, 0.5f);
					player.currentHealth -= baseDamage;
					attackTimer = 0.0f;
				}
			}
		}
	}
	//velocity = glm::vec3(0.0f);
	position += velocity * deltaTime;
}

void Enemy::receiveKnockback(const glm::vec3& knockback, const float& distance)
{
	knockbackVelocity = knockback;
	knockbackTimer = distance;
	isAttackable = false;
}
