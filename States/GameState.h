#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"

class Game;

class GameState : public BaseState
{
public:
	GameState(Game& game);

	bool update(sf::Time deltaTime);
	void render(sf::RenderTarget& target);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);
};

#endif // !GAMESTATE_H
