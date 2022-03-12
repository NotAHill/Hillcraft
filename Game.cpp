

#include "Game.h"

#include "States/TitleState.h"
#include "States/GameState.h"

Game::Game(sf::VideoMode size, sf::String title, bool fullscreen) :
	context(size, title, fullscreen)
{
	srand(time(0));

	stack.pushState<TitleState>(*this);
}

void Game::run()
{
	sf::Clock timer;

	while (context.window.isOpen())
	{
		sf::Time deltaTime = timer.restart();

		update(deltaTime);

		if (stack.isEmpty())
			context.window.close();

		handleEvents();

		render();
	}
}

Camera& Game::getCamera()
{
	return camera;
}

StateStack& Game::getStack()
{
	return stack;
}

const sf::RenderWindow& Game::getWindow() const
{
	return context.window;
}

void Game::setCursor(bool state)
{
	context.window.setMouseCursorVisible(state);
}

void Game::update(sf::Time deltaTime)
{
	stack.update(deltaTime);
	camera.update();
	Statistics::get().update(deltaTime);
}

void Game::render()
{
	stack.render(masterRenderer);
	Statistics::get().render(masterRenderer);
	masterRenderer.finishRender(context.window, camera);
}

void Game::handleEvents()
{
	sf::Event event;
	while (context.window.pollEvent(event))
	{
		stack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			context.window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				context.window.close();
			if (event.key.code == sf::Keyboard::V)
				Statistics::get().toggle();
		}
	}
}
