#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player : public Entity
{
public:
	Player();

	void handleInput(const sf::RenderWindow& window);
	void update(float deltaTime);
	const Vector3& getVelocity();

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	Vector3 velocity;
};



#endif // !PLAYER_H
