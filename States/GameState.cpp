#include "GameState.h"
#include "PauseState.h"

#include "../Game.h"
#include "../Config.h"

#include "../Command/MoveCommand.h"
#include "../Command/DialogueCommand.h"
#include "../Command/SpawnCommand.h"
#include "../Command/FunctionCommand.h"

#include "../Maths/RayCaster.h"
#include "../Entities/Enemy.h"
#include "../Entities/Friendly.h"
#include "../GUI/Label.h"

#include <iostream>
#include <iomanip>
#include <glm/gtx/string_cast.hpp>

GameState::GameState(Game& game) :
	BaseState(game),
	showWireframe(false),
	directionLight({0, 0, 0}, { 0.0f,-1.0f,0.0f }, { 0.8f,0.95f,0.95f }, { 0.15f, 0.8f, 0.5f }),
	secondLight({ 0, 0, 0 }, { 0.1f, -1.0f, -0.0f }, { 0.8f,0.95f,0.95f }, { 0.0f, 0.3f, 0.6f }),
	enemyModel("sphere", "rock"),
	friendModel("stall", "shop"),
	testObject(std::make_shared<Object>(enemyModel, glm::vec3{ 10.0f, 0, 0 }, glm::vec3{ 0, 0, 0 }, 2.0f))
{
	std::cout << "Currently in GAME state" << std::endl;
	
	gamePtr->getCamera().hookEntity(player); 
	auto window = gamePtr->getWindow().getSize();

	crosshair.setTexture(ResourceManager::get().textures.get("crosshair"));
	crosshair.setScale(2.0f, 2.0f);
	crosshair.setOrigin(crosshair.getLocalBounds().width / 2, crosshair.getLocalBounds().height / 2);
	crosshair.setPosition(window.x / 2, window.y / 2);

	healthBar = std::make_shared<Label>(false);
	healthBar->setText({ "Health: " + std::to_string(player.currentHealth) + "/" + std::to_string(player.maxHealth) });
	healthBar->setPosition(window.x - 320.0f, 50.0f);
	guiContainer.addComponent(healthBar);

	killCounter = std::make_shared<Label>(false);
	killCounter->setText({ "Kills: " + std::to_string(player.killCount) });
	killCounter->setPosition(window.x - 320.0f, 120.0f);
	guiContainer.addComponent(killCounter);
}

GameState::~GameState()
{
	Statistics::get().clearStaticText();
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

		healthBar->setText({ "Health: " + std::to_string(player.currentHealth) + "/" + std::to_string(player.maxHealth) });
		killCounter->setText({ "Kills: " + std::to_string(player.killCount) });
		updateStory(deltaTime.asSeconds());
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
							std::cout << "Enemy clicked" << std::endl;
							auto knockbackDir = glm::normalize(enemy->position - player.position);
							if (enemy->isAttackable)
							{
								enemy->receiveKnockback(knockbackDir, 1.0f);
								enemy->currentHealth -= player.baseDamage;
							}
						}
						else if (friendly)
						{
							std::cout << "friendly Clicked" << std::endl;
							friendly->interact(*this, player);
							firstInteraction = true;
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

	guiContainer.render(renderer);

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
	guiContainer.handleEvent(event, gamePtr->getWindow());
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
			//script.addCommand(std::make_unique<SpawnCommand>(std::make_shared<Enemy>(enemyModel, player.position, glm::vec3(0.0f), 1.0f), world, 0.0f));
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

void GameState::addDialogue(std::vector<std::string> lines, float timer)
{
	auto dialogue = std::make_shared<Label>(false, timer);
	dialogue->setText(lines);
	dialogue->setPosition(50.0f, 50.0f);
	guiContainer.addComponent(dialogue);
}

void GameState::updateStory(float deltaTime)
{
	static float timer = 0.0f;
	timer += deltaTime;

	static auto step = glm::vec3(0.0f);
	static bool secondMission = false;
	static bool firstMission = true;
	static bool tutorialComplete = false;
	static bool doOnce = true;
	static std::vector<glm::vec3> enemies;

	if (firstMission)
	{
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "Welcome!",  "This is the narrator speaking..." }));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "In this game,",  "your objective is to survive", "from the swarms of enemies"}));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "In a moment",  "you will be transported" }));
		script.addCommand(std::make_unique<MoveCommand>(player, glm::vec3{ 50.0f, 10, 50.0f }, 5.0f));
		
		script.addCommand(std::make_unique<FunctionCommand>([&]()
			{
				RayCaster testRay(player.position, player.rotation);
				testRay.step(35.0f);
				step = testRay.getEnd();
			}, 0.0f));
		
		script.addCommand(std::make_unique<SpawnCommand>(std::make_shared<Enemy>(enemyModel, step, glm::vec3(0.0f), 1.0f), world, step, 2.0f));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "This is an enemy",  "They will attack once you're in their range", "so beware!"}));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "Quick!", "Use left mouse button to attack!"}));
	
		firstMission = false;
		std::cout << "First mission done" << std::endl;
	}

	if (!firstMission && !secondMission && doOnce)
	{
		// The command should only be added when the queue is empty and enemies are also empty
		if (world.getCurrentChunk()->getEnemies().empty() && script.isEmpty())
		{
			secondMission = true;
			doOnce = false;
		}
	}

	if (secondMission)
	{
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "Well done!", 
			"You defeated your first enemy!", "The job only gets harder now!" }));
		script.addCommand(std::make_unique<FunctionCommand>([&]()
			{
				RayCaster testRay(player.position, player.rotation);
				testRay.step(25.0f);
				step = testRay.getEnd();
				step.y = world.getChunkAt(step.x, step.z)->getHeightOfTerrain(step.x, step.z);
			}, 0.0f));
		script.addCommand(std::make_unique<SpawnCommand>(std::make_shared<Friendly>(friendModel, step, glm::vec3(0.0f, rand(), 0.0f), 1.0f), world, step, 2.0f));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "This is a shop!", 
			"Currently all shops are closed", "However, you can still interact with them"}));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>{ "Narrator:", "Try going to one!"}));
		secondMission = false;
	}

	if (!secondMission && !firstMission && firstInteraction && !tutorialComplete)
	{
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>
		{ "Narrator:", "Well done!", "You have completed the tutorial!", "Now you are ready to fight", "Take this as a bonus :)"}));
		script.addCommand(std::make_unique<FunctionCommand>([&]()
			{
				player.maxHealth += 100.0f;
				player.currentHealth = player.maxHealth;
			}, 0.0f));
		script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>
		{ "System:", "For your brave actions,", "you have been awarded:", "+100 max health, +100 health"}));
		
		tutorialComplete = true;
	}

	//if (tutorialComplete && (rand() % 500 == 0))
	//{
	//	int count = rand() % 10;
	//	enemies.resize(count);
	//	script.addCommand(std::make_unique<FunctionCommand>([&]()
	//		{
	//			for (int i = 0; i < count; i++)
	//			{
	//				RayCaster testRay(player.position, {player.rotation.x, player.rotation.y + rand(), player.rotation.z });
	//				testRay.step(35.0f);
	//				enemies.push_back(testRay.getEnd());
	//			}
	//		}, 2.0f));
	//	for (int i = 0; i < count; i++)
	//		script.addCommand(std::make_unique<SpawnCommand>(std::make_shared<Enemy>(enemyModel, enemies[i], glm::vec3(0.0f), 1.0f), world, enemies[i], 2.0f + sinf((float)rand() / (float)RAND_MAX)));
	//	script.addCommand(std::make_unique<DialogueCommand>(*this, std::vector<std::string>
	//	{ "Narrator:", "A random group of enemies have arrived", "Quick!", "Try and teach them a lesson!"}));
	//}

}
