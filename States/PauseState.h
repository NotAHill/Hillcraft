#pragma once
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "BaseState.h"

#include "../GUI/Container.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Game;
class RenderMaster;

class PauseState : public BaseState
{
public:
	PauseState(Game& game);

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	Container container;

	sf::RectangleShape backgroundShape;
	sf::Text text;
};



#endif // !PAUSESTATE_H
