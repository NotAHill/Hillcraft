

#include "Game.h"

#include "States/TitleState.h"

Game::Game(sf::VideoMode size, sf::String title, bool fullscreen) :
	context(size, title, fullscreen)
{
	ResourceManager::get().fonts.load("Fixedsys.ttf");
	ResourceManager::get().fonts.load("Sansation.ttf");
	ResourceManager::get().textures.load("vector.jpg", "background");
	ResourceManager::get().shaders.loadShader("basic_vertex.glsl", "basic_fragment.glsl", "basic_shader");

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

StateStack& Game::getStack()
{
	return stack;
}

const sf::RenderWindow& Game::getWindow() const
{
	return context.window;
}

void Game::update(sf::Time deltaTime)
{
	stack.update(deltaTime);
}

void Game::render()
{
	stack.render(masterRenderer);
	masterRenderer.finishRender(context.window);
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
			if (event.key.code == sf::Keyboard::Escape)
				context.window.close();
	}
}
