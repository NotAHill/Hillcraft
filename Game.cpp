#include <glad/glad.h>

#include "Game.h"

#include "States/TitleState.h"

Game::Game(sf::VideoMode size, sf::String title, bool fullscreen) :
	stack(),
	tickSpeed(sf::seconds(1.0f/60.0f)),
	fonts("res/fonts/"),
	textures("res/textures/")
{
	// Configure OpenGL context settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	// Create our window with specified context settings
	if (fullscreen)
		window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Fullscreen, settings);
	else
		window.create(size, title, sf::Style::Close | sf::Style::Titlebar, settings);

	// Load OpenGL function pointers
	//gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))
	if (!gladLoadGL())
	{
		std::cerr << "Unable to load OpenGL functions\n";
		exit(-1);
	}

	// Create the OpenGL viewport
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	fonts.load("Fixedsys.ttf");
	fonts.load("Sansation.ttf");

	textures.load("vector.jpg", "background");

	stack.pushState<TitleState>(*this);
}

void Game::run()
{
	sf::Clock timer;

	while (window.isOpen())
	{
		sf::Time deltaTime = timer.restart();

		update(deltaTime);

		if (stack.isEmpty())
			window.close();

		handleEvents();

		render();
	}
}

StateStack& Game::getStack()
{
	return stack;
}

ResourceHolder<sf::Font>& Game::getFonts()
{
	return fonts;
}

ResourceHolder<sf::Texture>& Game::getTextures()
{
	return textures;
}

ResourceHolder<sf::Shader>& Game::getShaders()
{
	return shaders;
}

const sf::RenderWindow& Game::getWindow() const
{
	return window;
}

//sf::RenderWindow& Game::getWindow()
//{
//	return window;
//}

void Game::update(sf::Time deltaTime)
{
	stack.update(deltaTime);
}

void Game::render()
{
	window.clear();
	stack.render(window);
	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
	}
}
