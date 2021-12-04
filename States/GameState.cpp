#include "GameState.h"
#include "PauseState.h"
#include "../Game.h"

#include <iostream>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(false)
{
	std::cout << "Currently in GAME state" << std::endl;
}

bool GameState::update(sf::Time deltaTime)
{
	return true;
}

void GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	renderer.drawQuad({ 0, 0, 0 });
}

bool GameState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool GameState::handleEvent(sf::Event& event)
{
	// If any key is pressed move to the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Backspace)
			gamePtr->getStack().pushState<PauseState>(*gamePtr);
		if (event.key.code == sf::Keyboard::P)
			showWireframe = !showWireframe;

	}

	return true;
}
