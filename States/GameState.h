#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "../Entities/Player.h"
#include "../World/Light.h"
#include "../World/World.h"
#include "../Entities/Object.h"
#include "../Command/ScriptEngine.h"

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

	// TEMP
	TexturedModel testModel;
	std::shared_ptr<Object> testObject;

	World world;
	Player player;
	ScriptEngine script;
	sf::Sprite crosshair;

	// Lights
	Light directionLight;
	Light secondLight;
};

#endif // !GAMESTATE_H
