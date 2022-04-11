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
	int maxHealth;
	int killCount;

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	bool inAir;
	bool flyMode;
	glm::vec3 knockbackVelocity;
	float knockbackTimer;	
};


#endif // !PLAYER_H

