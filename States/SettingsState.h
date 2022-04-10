#pragma once
#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H


#include "BaseState.h"
#include "../GUI/Container.h"

#include <SFML/Graphics.hpp>

class Game;
class RenderMaster;

class SettingsState : public BaseState
{
public:
	SettingsState(Game& game);

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	Container container;
};


#endif // !SETTINGS_STATE_H
