#pragma once
#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class Game;
class RenderMaster;

class BaseState : public sf::NonCopyable
{
public:
	BaseState(Game& game);
	virtual ~BaseState();

	virtual bool update(sf::Time deltaTime) = 0;
	virtual bool fixedUpdate(sf::Time deltaTime) = 0;
	virtual bool render(RenderMaster& renderer) = 0;
	virtual bool handleEvent(sf::Event& event) = 0;

protected:
	Game* gamePtr;
};

#endif // !BASESTATE_H
