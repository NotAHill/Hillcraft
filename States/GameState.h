#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "../Entities/Player.h"
#include "../World/Terrain.h"
#include "../World/Light.h"

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
	Terrain terrain;
	Player player;
	Light directionLight;

	sf::Text infoText;
};

#endif // !GAMESTATE_H
