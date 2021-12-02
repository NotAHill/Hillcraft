#include "Game.h"

#include "States/TitleState.h"

Game::Game(sf::VideoMode size, sf::String title, bool fullscreen) :
	window(size, title, sf::Style::Close | sf::Style::Titlebar | (sf::Style::Fullscreen * fullscreen)),
	stack(),
	tickSpeed(sf::seconds(1.0f/60.0f)),
	fonts("res/fonts/"),
	textures("res/textures/")
{
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

const sf::RenderWindow& Game::getWindow() const
{
	return window;
}

sf::RenderWindow& Game::getWindow()
{
	return window;
}

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
