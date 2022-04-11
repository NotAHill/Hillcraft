#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"

#include "../World/Light.h"
#include "../World/World.h"
#include "../Command/ScriptEngine.h"
#include "../Entities/Player.h"
#include "../GUI/Container.h"
#include "../GUI/Label.h"

class Game;

class GameState : public BaseState
{
public:
	GameState(Game& game);
	~GameState();

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);
	void addDialogue(std::vector<std::string> lines, float timer);
	
	ScriptEngine script;
private:
	void updateStory(float deltaTime);

	bool showWireframe;

	// Entities
	std::vector<Object> objects;

	// TEMP
	TexturedModel enemyModel;
	TexturedModel friendModel;
	std::shared_ptr<Object> testObject;

	World world;
	Player player;
	
	sf::Sprite crosshair;

	// Lights
	Light directionLight;
	Light secondLight;

	// GUI
	Container guiContainer;
	std::shared_ptr<Label> healthBar;
	std::shared_ptr<Label> killCounter;

	bool firstInteraction = false;
};

#endif // !GAMESTATE_H
