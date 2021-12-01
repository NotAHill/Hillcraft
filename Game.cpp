#include "Game.h"

#include "States/TitleState.h"

Game::Game(sf::VideoMode size, sf::String title, bool fullscreen) :
	window(size, title, sf::Style::Close | sf::Style::Titlebar | (sf::Style::Fullscreen * fullscreen)),
	stack(),
	tickSpeed(sf::seconds(1.0f/60.0f))
{
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

		render();

		handleEvents();
	}
}

StateStack& Game::getStack()
{
	return stack;
}

const sf::RenderWindow& Game::getWindow() const
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
