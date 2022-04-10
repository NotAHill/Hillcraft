
#pragma once
#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "BaseState.h"
#include "../GUI/Container.h"

#include <SFML/Graphics.hpp>

class Game;
class RenderMaster;

class MenuState : public BaseState
{
public:
	MenuState(Game& game);

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	Container container;
};

#endif // !MENU_STATE_H
