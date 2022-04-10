#pragma once
#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "BaseState.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Game;
class RenderMaster;

class TitleState : public BaseState
{
public:
	TitleState(Game& game);

	bool update(sf::Time deltaTime);
	bool render(RenderMaster& renderer);
	bool fixedUpdate(sf::Time deltaTime);
	bool handleEvent(sf::Event& event);

private:
	sf::Sprite backgroundSprite;
	sf::Text text;
	sf::Time timer;
	bool showText;
};



#endif // !TITLESTATE_H
