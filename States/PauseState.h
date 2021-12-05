#pragma once
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "BaseState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

class Game;
class RenderMaster;

class PauseState : public BaseState
{
public:
	PauseState(Game& game);

	bool update(float deltaTime);
	void render(RenderMaster& renderer);
	bool fixedUpdate(float deltaTime);
	bool handleEvent(sf::Event& event);

private:
	sf::RectangleShape backgroundShape;
	sf::Text text;

	float timer;
	sf::Text timerText;
};



#endif // !PAUSESTATE_H
