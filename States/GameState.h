#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "../Entities/Player.h"
#include "../World/Light.h"
#include "../World.h"
#include "../Entities/Object.h"

class Game;

class GameState : public BaseState
{
public:
	GameState(Game& game);

	bool update(sf::Time deltaTime);
	void render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	bool showWireframe;

	// Entities
	std::vector<Object> objects;
	World world;
	Player player;

	// Lights
	Light directionLight;
	Light secondLight;

	// Models for each type of object
	TexturedModel rock;
	TexturedModel tree;
};

#endif // !GAMESTATE_H
