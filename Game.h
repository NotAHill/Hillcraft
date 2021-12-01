#pragma once
#ifndef GAME_H
#define GAME_H

#include "States/StateStack.h"
#include "States/BaseState.h"
#include "States/TitleState.h"
#include "States/GameState.h"

#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(sf::VideoMode size = { 1280, 640 }, 
		 sf::String title = "Project", 
		 bool fullscreen = false);
	void run();

	StateStack& getStack();
	ResourceHolder<sf::Font>& getFonts();
	ResourceHolder<sf::Texture>& getTextures();

	const sf::RenderWindow& getWindow() const;
	sf::RenderWindow& getWindow();

private:
	sf::RenderWindow window;
	StateStack stack;
	
	ResourceHolder<sf::Font> fonts;
	ResourceHolder<sf::Texture> textures;

	const sf::Time tickSpeed;

	void update(sf::Time deltaTime);
	void render();
	void handleEvents();
};

#endif // !GAME_H
