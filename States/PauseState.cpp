#include "PauseState.h"
#include "GameState.h"
#include "../Game.h"

#include <iostream>

PauseState::PauseState(Game& game) :
	BaseState(game),
	text(),
	timerText(),
	timer(sf::Time::Zero),
	backgroundShape()
{
	text.setFont(ResourceManager::get().fonts.get("Fixedsys"));
	text.setString("Game Paused");
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);
	text.setCharacterSize(48u);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(gamePtr->getWindow().getSize() / 2u));

	timerText.setFont(ResourceManager::get().fonts.get("Sansation"));
	timerText.setFillColor(sf::Color::Blue);
	timerText.setOutlineColor(sf::Color::Black);
	timerText.setOutlineThickness(3.0f);
	timerText.setCharacterSize(48u);
	//timerText.setPosition(sf::Vector2f(gamePtr->getWindow().getSize() / 2u));

	backgroundShape.setFillColor({ 0, 0, 0, 150 });
	backgroundShape.setSize(sf::Vector2f(gamePtr->getWindow().getSize()));


	std::cout << "Currently in PAUSE state" << std::endl;
}

bool PauseState::update(sf::Time deltaTime)
{
	// Return false so that all the states below it on the stack are not updated
	return false;
}

void PauseState::render(RenderMaster& renderer)
{
	renderer.drawSFML(backgroundShape);
	renderer.drawSFML(text);
	renderer.drawSFML(timerText);
}

bool PauseState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool PauseState::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::BackSpace)
		{
			// Backspace pressed, remove itself to return to the game
			gamePtr->getStack().popState();
		}
	}

	return false;
}
