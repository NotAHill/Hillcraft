#include "GameState.h"
#include "../Game.h"

#include <iostream>

GameState::GameState(Game& game) :
	BaseState(game)
{
	std::cout << "Currently in GAME state" << std::endl;
}

bool GameState::update(sf::Time deltaTime)
{
	return true;
}

void GameState::render(sf::RenderTarget& target)
{
	// Pass for now...
}

bool GameState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool GameState::handleEvent(sf::Event& event)
{
	// If any key is pressed move to the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		gamePtr->getStack().popState();
	}

	return true;
}
