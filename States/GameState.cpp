#include "GameState.h"
#include "PauseState.h"

#include "../Game.h"
#include "../Config.h"
#include "../Command/MoveCommand.h"
#include "../Command/DialogueCommand.h"
#include "../Maths/RayCaster.h"
#include "../Entities/Enemy.h"
#include "../Entities/Friendly.h"

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

	dialogueText.setFont(ResourceManager::get().fonts.get("Fixedsys"));
	dialogueText.setOutlineColor(sf::Color::Black);
	dialogueText.setOutlineThickness(2.0f);

	dialogueBox.setOutlineColor(sf::Color::Black);
	dialogueBox.setFillColor(sf::Color::Blue);
	dialogueBox.setOutlineThickness(6.0f);
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
		world.updateChunks(deltaTime.asSeconds(), player);
		player.update(deltaTime.asSeconds(), *world.getCurrentChunk());
		
		Statistics::get().addText("Position: (" + to_string(player.position) + ")\n" +
			"Rotation: (" + to_string(player.rotation) + ")\n" +
			"Velocity: (" + to_string(player.getVelocity()) + ")");

		script.processCommands(deltaTime.asSeconds());

		if (!player.isAlive)
		{
			// Reset game
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<GameState>(*gamePtr);
		}

		//static float elapsedTime = 0.0f;
		//directionLight.direction = { 0.3f, -cosf(elapsedTime) , 0.5f };
		//if (directionLight.direction.y >= 0.2f) elapsedTime += 0.5f * deltaTime.asSeconds();
		//else elapsedTime += 0.1f * deltaTime.asSeconds();
		//Statistics::get().addText("Light Direction: (" + to_string(directionLight.direction) + ")");

		static sf::Clock timer;

		int count = 0;
		for (RayCaster ray(player.position, player.rotation); ray.getLength() < 10.0f; ray.step(0.1f))
		{
			for (auto& item : world.getLoadedObjects())
			{
				if (item->box.isPointInBox(ray.getEnd()))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asSeconds() > 0.2f)
					{
						timer.restart();
						auto enemy = std::dynamic_pointer_cast<Enemy>(item);
						auto friendly = std::dynamic_pointer_cast<Friendly>(item);
						// If the item is an enemy then attack
						if (enemy)
						{
							auto knockbackDir = glm::normalize(enemy->position - player.position);
							if (enemy->isAttackable)
							{
								enemy->receiveKnockback(knockbackDir, 1.0f);
								enemy->currentHealth -= player.baseDamage;
							}
						}
						else if (friendly)
						{
							static int counter = 0;
							std::vector<std::string> myText = { "Hello", "This is " + std::to_string(++counter) };
							script.addCommand(std::make_unique<DialogueCommand>(*this, myText));
							friendly->interact();
						}
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
		int a = 3;
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

	return false;
}

bool GameState::render(RenderMaster& renderer)
{
	if (showWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (showDialogue)
	{
		displayDialogue(dialogue, 20.0f, 20.0f);
		renderer.drawSFML(dialogueBox);
		renderer.drawSFML(dialogueText);
	}

	renderer.addLight(directionLight);
	renderer.drawSFML(crosshair);
	//renderer.addLight(secondLight);
	renderer.drawQuad({ 0, 0, 0 }, { 0, 0, 0 });
	renderer.drawWorld(world);
	renderer.drawObject(testObject);

	return false;
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
		if (event.key.code == sf::Keyboard::Enter)
		{
			if (showDialogue)
			{
				showDialogue = false;
				script.finishCommand();
			}
		}
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

	return false;
}

void GameState::addDialogue(std::vector<std::string> lines)
{
	dialogue = lines;
	showDialogue = true;
}

void GameState::displayDialogue(std::vector<std::string> lines, float x, float y)
{
	std::string text;
	for (int line = 0; line < lines.size(); line++)
		text += lines[line] + "\n";
	dialogueText.setString(text);

	auto rect = dialogueText.getGlobalBounds();
	dialogueBox.setSize({ rect.width + 20.0f, rect.height + 20.0f });
	dialogueBox.setPosition({ x, y });
	dialogueText.setPosition({ x + 10.0f, y + 10.0f });
}
