#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "BaseState.h"

#include "../World/Light.h"
#include "../World/World.h"
#include "../Command/ScriptEngine.h"
#include "../Entities/Player.h"

class Game;

class GameState : public BaseState
{
public:
	GameState(Game& game);

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);
	void addDialogue(std::vector<std::string> lines);
private:
	
	void displayDialogue(std::vector<std::string> lines, float x, float y);

	bool showWireframe;

	// Entities
	std::vector<Object> objects;

	// TEMP
	TexturedModel testModel;
	std::shared_ptr<Object> testObject;

	World world;
	Player player;
	ScriptEngine script;
	sf::Sprite crosshair;

	// Lights
	Light directionLight;
	Light secondLight;

	// RPG
	sf::RectangleShape dialogueBox;
	sf::Text dialogueText;
	std::vector<std::string> dialogue;
	bool showDialogue;
};

#endif // !GAMESTATE_H
