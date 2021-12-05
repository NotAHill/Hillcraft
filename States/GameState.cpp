#include "GameState.h"

#include "PauseState.h"
#include "../Util/ResourceManager.h"
#include "../Game.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(false)
{
	infoText.setFont(Resources().fonts.get("Fixedsys"));
	infoText.setCharacterSize(13u);

	gamePtr->getCamera().hookEntity(player);

	std::cout << "Currently in GAME state" << std::endl;
}

bool GameState::update(float deltaTime)
{

	player.handleInput(gamePtr->getWindow());
	infoText.setString("Player Position: " + glm::to_string(player.position) + "\n" +
	                   "Player Rotation: " + glm::to_string(player.rotation) + "\n" +
					   "Player Velocity: " + glm::to_string(player.getVelocity()) + "\n" +
					   "Camera Position: " + glm::to_string(gamePtr->getCamera().position) + "\n" +
					   "Camera Rotation: " + glm::to_string(gamePtr->getCamera().rotation));

	player.update(deltaTime);
	return true;
}

void GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	renderer.drawSFML(infoText);
	for (float i = 0; i < 3; ++i)
		for (float j = 0; j < 3; ++j)
			for (float k = 0; k < 3; ++k)
				renderer.drawQuad({ i, j, k });
}

bool GameState::fixedUpdate(float deltaTime)
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
