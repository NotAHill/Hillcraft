#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "../World/Terrain.h"

class Player : public Entity
{
public:
	Player();

	void handleInput(const sf::RenderWindow& window);
	void update(float deltaTime, Terrain& terrain);
	const glm::vec3& getVelocity();

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	glm::vec3 velocity;

	bool inAir;
	bool flyMode;

	const float GRAVITY = -0.5f;
	const float JUMP_STRENGTH = 18.0f;


};


#endif // !PLAYER_H

