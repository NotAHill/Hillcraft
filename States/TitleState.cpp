#include "TitleState.h"
#include "GameState.h"
#include "../Game.h"

#include <iostream>

TitleState::TitleState(Game& game) :
	BaseState(game),
	text(),
	timer(0.0f),
	showText(true)
{
	backgroundSprite.setTexture(Resources().textures.get("background"));

	// Set the sprite to screen size
	backgroundSprite.setScale(
		gamePtr->getWindow().getSize().x / backgroundSprite.getLocalBounds().width,
		gamePtr->getWindow().getSize().y / backgroundSprite.getLocalBounds().height);

	text.setFont(Resources().fonts.get("Fixedsys"));
	text.setString("Press any key to start");
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(3.0f);
	text.setCharacterSize(48u);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(gamePtr->getWindow().getSize() / 2u));
	
	std::cout << "Currently in TITLE state" << std::endl;
}

bool TitleState::update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= 0.5f)
	{
		showText = !showText;
		timer = 0.0f;
	}
	return true;
}

void TitleState::render(RenderMaster& renderer)
{
	renderer.drawSFML(backgroundSprite);

	if (showText)
		renderer.drawSFML(text);
}

bool TitleState::fixedUpdate(float deltaTime)
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
