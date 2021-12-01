#include "TitleState.h"
#include "GameState.h"
#include "../Game.h"

#include <iostream>

TitleState::TitleState(Game& game) :
	BaseState(game),
	text()
{
	backgroundSprite.setTexture(gamePtr->getTextures().get("background"));

	text.setFont(gamePtr->getFonts().get("Fixedsys"));
	text.setString("Press any key to start");
	text.setPosition(sf::Vector2f(gamePtr->getWindow().getSize() / 2u));
}

bool TitleState::update(sf::Time deltaTime)
{
	std::cout << "Currently in TITLE state" << std::endl;
	return true;
}

void TitleState::render(sf::RenderTarget& target)
{
	auto& window = gamePtr->getWindow();
	window.draw(backgroundSprite);
	window.draw(text);
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
