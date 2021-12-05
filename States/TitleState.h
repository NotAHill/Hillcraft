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

	bool update(float deltaTime);
	void render(RenderMaster& renderer);
	bool fixedUpdate(float deltaTime);
	bool handleEvent(sf::Event& event);

private:
	sf::Sprite backgroundSprite;
	sf::Text text;
	float timer;
	bool showText;
};



#endif // !TITLESTATE_H
