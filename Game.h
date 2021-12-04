#pragma once
#ifndef GAME_H
#define GAME_H


#include "Renderer/RenderMaster.h"

#include "States/StateStack.h"
#include "States/BaseState.h"
#include "States/TitleState.h"
#include "States/GameState.h"

#include "Util/ResourceHolder.h"
#include "Util/Shader.h"

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
	ResourceHolder<Shader>& getShaders();

	const sf::RenderWindow& getWindow() const;
	//sf::RenderWindow& getWindow();

private:
	sf::RenderWindow window;

	RenderMaster masterRenderer;
	StateStack stack;

	ResourceHolder<sf::Font> fonts;
	ResourceHolder<sf::Texture> textures;
	ResourceHolder<Shader> shaders;

	const sf::Time tickSpeed;

	void update(sf::Time deltaTime);
	void render();
	void handleEvents();
};

#endif // !GAME_H
