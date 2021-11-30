#pragma once
#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "BaseState.h"

class Game;

class TitleState : public BaseState
{
public:
	TitleState(Game& game);

	bool update(sf::Time deltaTime);
	void render(sf::RenderTarget& target);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);
};



#endif // !TITLESTATE_H
