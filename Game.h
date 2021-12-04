#pragma once
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include "Context.h"
#include "Renderer/RenderMaster.h"

#include "States/StateStack.h"
#include "States/BaseState.h"
#include "States/TitleState.h"
#include "States/GameState.h"

#include "Util/ResourceManager.h"

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::VideoMode size = { 1280, 640 }, 
		 sf::String title = "Project", 
		 bool fullscreen = false);
	void run();

	StateStack& getStack();
	const sf::RenderWindow& getWindow() const;

private:
	Context context;
	RenderMaster masterRenderer;
	StateStack stack;

	void update(sf::Time deltaTime);
	void render();
	void handleEvents();
};

#endif // !GAME_H
