#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Component.h"

#include <functional>

enum class TextboxSize
{
	SMALL,
	WIDE
};

class Textbox : public Component
{
public:
	Textbox(TextboxSize size = TextboxSize::WIDE);

	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void render(RenderMaster& renderer);

	void select();
	void deselect();

	void activate();
	void deactivate();

	void setCallback(std::function<void(const std::string&)> _callback);

	void setPosition(const float& x, const float& y);
	void setPosition(const sf::Vector2f& _position);

protected:
	Rectangle rect;
	Text text;
	std::string textBuffer;

	std::function<void(const std::string&)> onEnter;
};


#endif // !TEXTBOX_H


