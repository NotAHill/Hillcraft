#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "DynamicCreature.h"
#include "../World/Terrain.h"

class Player : public DynamicCreature
{
public:
	Player(TexturedModel& _model, glm::vec3 _position = { 10.f, 10.f, 10.f }, glm::vec3 _rotation = { 0, 180.f, 0 }, float _scale = 1.0f);

	void handleInput(const sf::RenderWindow& window);
	void handleEvent(const sf::Event& event);
	void toggleFlight();
	void update(float deltaTime, Terrain& terrain);
	const glm::vec3& getVelocity();
	void attack();
	void onInteract(Dynamic& player);

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	glm::vec3 velocity;

	bool inAir;
	bool flyMode;
};


#endif // !PLAYER_H

