#include "GameState.h"
#include "PauseState.h"
#include "../Game.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(true)
{
	std::cout << "Currently in GAME state" << std::endl;
	gamePtr->getCamera().hookEntity(player);

	infoText.setFont(ResourceManager::get().fonts.get("Fixedsys"));
	infoText.setFillColor(sf::Color::White);
	infoText.setOutlineColor(sf::Color::Black);
	infoText.setOutlineThickness(1.0f);
	infoText.setCharacterSize(26u);
	infoText.setPosition(0.f, 50.f);
}

bool GameState::update(sf::Time deltaTime)
{
	if (gamePtr->getWindow().hasFocus())
	{
		gamePtr->setCursor(false);
		player.handleInput(gamePtr->getWindow());
		player.update(deltaTime.asSeconds());
	}

	infoText.setString("Position: " + glm::to_string(player.position) + "\n" +
					   "Rotation: " + glm::to_string(player.rotation)); 
		//+ "\n" + "Velocity: " + glm::to_string(player.getVelocity()));

	return true;
}

void GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	renderer.drawQuad({ 5, 2, 5 });
	renderer.drawTerrain({ 0, 0, 0 });
	renderer.drawSFML(infoText);
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
		{
			gamePtr->setCursor(true);
			gamePtr->getStack().pushState<PauseState>(*gamePtr);
		}
		if (event.key.code == sf::Keyboard::P)
			showWireframe = !showWireframe;

	}

	return true;
}
