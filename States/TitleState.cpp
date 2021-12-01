#include "TitleState.h"
#include "GameState.h"
#include "../Game.h"

#include <iostream>

TitleState::TitleState(Game& game) :
	BaseState(game)
{
}

bool TitleState::update(sf::Time deltaTime)
{
	std::cout << "title state" << std::endl;
	return true;
}

void TitleState::render(sf::RenderTarget& target)
{
	// Pass for now...
}

bool TitleState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool TitleState::handleEvent(sf::Event& event)
{
	// If any key is pressed move to the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		//auto& stack = gamePtr->getStack();	// Vector empty before pop
		gamePtr->getStack().popState();	
		gamePtr->getStack().pushState<GameState>(*gamePtr);		// Read access violation
		return false;
	}

	return true;
}
