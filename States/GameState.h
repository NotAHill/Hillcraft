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
	void render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	bool showWireframe;
};

#endif // !GAMESTATE_H
