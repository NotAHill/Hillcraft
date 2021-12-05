#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"
#include "../Player.h"
#include <SFML/Graphics/Text.hpp>

class Game;

class GameState : public BaseState
{
public:
	GameState(Game& game);

	bool update(float deltaTime);
	void render(RenderMaster& renderer);
	bool fixedUpdate(float deltaTime);
	bool handleEvent(sf::Event& event);

private:
	bool showWireframe;
	Player player;
	sf::Text infoText;
};

#endif // !GAMESTATE_H
