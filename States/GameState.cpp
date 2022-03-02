#include "GameState.h"
#include "PauseState.h"
#include "../Game.h"
#include "../Config.h"

#include <iostream>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(false),
	terrain(20.0f, 100.0f, 200),
	directionLight({0, 0, 0}, { 0.3f,-1.0f,0.5f }, { 1.0f,1.0f,1.0f }, { 0.1f, 1.0f, 0.5f }),
	secondLight({ 0, 0, 0 }, { 0.7f, -1.0f, -0.2f }, { 0.8f,1.0f,0.1f }, { 0.0f, 0.0f, 0.6f })
{
	std::cout << "Currently in GAME state" << std::endl;
	gamePtr->getCamera().hookEntity(player);
}

bool GameState::update(sf::Time deltaTime)
{
	if (gamePtr->getWindow().hasFocus())
	{
		gamePtr->setCursor(false);
		player.handleInput(gamePtr->getWindow());
		player.update(deltaTime.asSeconds(), terrain);
	}

	auto to_string = [](const glm::vec3& v) { return std::to_string(v.x) + ", " +
													 std::to_string(v.y) + ", " +
													 std::to_string(v.z); };

	Statistics::get().addText("Position: (" + to_string(player.position) + ")\n" +
					   "Rotation: (" + to_string(player.rotation) + ")\n" + 
					   "Velocity: (" + to_string(player.getVelocity()) + ")");

	return true;
}

void GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	
	renderer.addLight(directionLight);
	renderer.addLight(secondLight);
	renderer.drawQuad(
		{ 0, 0, 0 },
		{ 0, 0, 0 });
	renderer.drawTerrain(terrain);
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
		if (event.key.code == sf::Keyboard::F)
			player.toggleFlight();

	}

	return true;
}
