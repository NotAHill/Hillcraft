#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../World/Terrain.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:
	Player();

	void handleInput(const sf::RenderWindow& window);
	void toggleFlight();
	void update(float deltaTime, Terrain& terrain);
	const glm::vec3& getVelocity();
	void receiveKnockback(const glm::vec3& knockback, const float& time);

	int baseDamage;
	int currentHealth;
	bool isAttackable;
	bool isAlive;

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	glm::vec3 velocity;

	bool inAir;
	bool flyMode;
	int maxHealth;
	glm::vec3 knockbackVelocity;
	float knockbackTimer;	
};


#endif // !PLAYER_H

