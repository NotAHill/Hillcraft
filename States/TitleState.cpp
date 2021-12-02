#include "TitleState.h"
#include "GameState.h"
#include "../Game.h"

#include <iostream>

TitleState::TitleState(Game& game) :
	BaseState(game),
	text(),
	timer(sf::Time::Zero),
	showText(true)
{
	backgroundSprite.setTexture(gamePtr->getTextures().get("background"));

	// Set the sprite to screen size
	backgroundSprite.setScale(
		gamePtr->getWindow().getSize().x / backgroundSprite.getLocalBounds().width,
		gamePtr->getWindow().getSize().y / backgroundSprite.getLocalBounds().height);

	text.setFont(gamePtr->getFonts().get("Fixedsys"));
	text.setString("Press any key to start");
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);
	text.setCharacterSize(48u);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(gamePtr->getWindow().getSize() / 2u));
	
	std::cout << "Currently in TITLE state" << std::endl;
}

bool TitleState::update(sf::Time deltaTime)
{
	timer += deltaTime;

	if (timer >= sf::seconds(0.5f))
	{
		showText = !showText;
		timer = sf::Time::Zero;
	}
	return true;
}

void TitleState::render(sf::RenderTarget& target)
{
	target.draw(backgroundSprite);

	if (showText)
		target.draw(text);
}

bool TitleState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool TitleState::handleEvent(sf::Event& event)
{
	// If any key is pressed move to the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		gamePtr->getStack().popState();	
		gamePtr->getStack().pushState<GameState>(*gamePtr);
	}

	return true;
}
