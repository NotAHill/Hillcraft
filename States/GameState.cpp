#include "GameState.h"
#include "PauseState.h"
#include "../Game.h"
#include "../Config.h"
#include "../Command/MoveCommand.h"
#include "../Maths/RayCaster.h"

#include <iostream>
#include <iomanip>
#include <glm/gtx/string_cast.hpp>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(false),
	directionLight({0, 0, 0}, { 0.0f,-1.0f,0.0f }, { 0.8f,0.95f,0.95f }, { 0.15f, 0.8f, 0.5f }),
	secondLight({ 0, 0, 0 }, { 0.1f, -1.0f, -0.0f }, { 0.8f,0.95f,0.95f }, { 0.0f, 0.3f, 0.6f }),
	testModel("toonRocks", "tree"),
	testObject(std::make_shared<Object>(testModel, glm::vec3{ 10.0f, 0, 0 }, glm::vec3{ 0, 0, 0 }, 2.0f))
{
	std::cout << "Currently in GAME state" << std::endl;
	gamePtr->getCamera().hookEntity(player);

	crosshair.setTexture(ResourceManager::get().textures.get("crosshair"));
	crosshair.setScale(2.0f, 2.0f);
	crosshair.setOrigin(crosshair.getLocalBounds().width / 2, crosshair.getLocalBounds().height / 2);
	crosshair.setPosition(gamePtr->getWindow().getSize().x / 2, gamePtr->getWindow().getSize().y / 2);
}

bool GameState::update(sf::Time deltaTime)
{
	auto float_to_str = [&](const float& val, const int& dp)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(dp) << val;
		return stream.str();
	};


	auto to_string = [&](const glm::vec3& v) 
	{ return float_to_str(v.x, 1) + ", " + float_to_str(v.y, 1) + ", " + float_to_str(v.z, 1); };


	if (gamePtr->getWindow().hasFocus())
	{
		gamePtr->setCursor(false);
		player.handleInput(gamePtr->getWindow());
		world.updateChunks(player);
		player.update(deltaTime.asSeconds(), *world.getCurrentChunk());
		
		Statistics::get().addText("Position: (" + to_string(player.position) + ")\n" +
			"Rotation: (" + to_string(player.rotation) + ")\n" +
			"Velocity: (" + to_string(player.getVelocity()) + ")");

		script.processCommands(deltaTime.asSeconds());

		//static float elapsedTime = 0.0f;
		//directionLight.direction = { 0.3f, -cosf(elapsedTime) , 0.5f };
		//if (directionLight.direction.y >= 0.2f) elapsedTime += 0.5f * deltaTime.asSeconds();
		//else elapsedTime += 0.1f * deltaTime.asSeconds();
		//Statistics::get().addText("Light Direction: (" + to_string(directionLight.direction) + ")");

		int count = 0;
		for (RayCaster ray(player.position, player.rotation); ray.getLength() < 6; ray.step(0.1f))
		{
			for (auto& item : world.getLoadedObjects())
			{
				if (item->box.isPointInBox(ray.getEnd()))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						count = 1;
						goto first;
					}
					else
					{
						count = 2;
						goto first;
					}
				}
			}
		}

	first:
		switch (count)
		{
		case 0:
			Statistics::get().addText("Not touching anything");
			break;
		case 1:
			Statistics::get().addText("Click");
			break;
		case 2:
			Statistics::get().addText("Hover");
			break;
		}
	}

	return true;
}

void GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	renderer.addLight(directionLight);
	renderer.drawSFML(crosshair);
	//renderer.addLight(secondLight);
	renderer.drawQuad({ 0, 0, 0 }, { 0, 0, 0 });
	renderer.drawWorld(world);
	renderer.drawObject(testObject);
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
		if (event.key.code == sf::Keyboard::J)
			script.addCommand(std::make_unique<MoveCommand>(*testObject, player.position, 3.0f, false));

	}

//	int count = 0;
//	for (RayCaster ray(player.position, player.rotation); ray.getLength() < 6; ray.step(0.1f))
//	{
//		for (auto& item : world.getLoadedObjects())
//		{
//			if (item->box.isPointInBox(ray.getEnd()))
//			{
//				if (event.type == sf::Event::MouseButtonPressed)
//				{
//					count = 1;
//					goto first;
//				}
//				
//				else
//				{
//					count = 2;
//					goto first;
//				}
//			}
//		}
//	}
//
//first:
//	switch (count)
//	{
//	case 0:
//		Statistics::get().addText("Not touching anything");
//		break;
//	case 1:
//		Statistics::get().addText("Click");
//		break;
//	case 2:
//		Statistics::get().addText("Hover");
//		break;
//	}

	return true;
}
