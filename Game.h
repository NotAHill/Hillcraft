#pragma once
#ifndef GAME_H
#define GAME_H

#include "States/StateStack.h"

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
	sf::RenderWindow window;
	StateStack stack;

	const sf::Time tickSpeed;

	void update(sf::Time deltaTime);
	void render();
	void handleEvents();
};

#endif // !GAME_H
