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

#include "Entities/Camera.h"

#include "Util/Statistics.h"

class Game
{
public:
	Game(sf::VideoMode size = { 1280, 640 }, 
		 sf::String title = "Project", 
		 bool fullscreen = false);
	void run();

	Camera& getCamera();
	StateStack& getStack();
	const sf::RenderWindow& getWindow() const;
	void setCursor(bool state);

private:
	Context context;
	RenderMaster masterRenderer;
	StateStack stack;
	Camera camera;
	Statistics fpsCounter;

	void update(sf::Time deltaTime);
	void render();
	void handleEvents();
};

#endif // !GAME_H
