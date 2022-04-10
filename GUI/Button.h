#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"

#include <functional>

enum class ButtonSize
{
	XSMALL,
	SMALL,
	WIDE
};

class Button : public Component
{
public:
	Button(ButtonSize size = ButtonSize::WIDE, bool _centerOrigin = true);

	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void render(RenderMaster& renderer);

	void setCallback(std::function<void(void)> _callback);
	void setText(const std::string& _text);
	void setToggle(const bool& _toggle);
	void setPosition(const float& x, const float& y);
	void setPosition(const sf::Vector2f& _position);

	void select();
	void deselect();
	void activate();
	void deactivate();

	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;

protected:
	void updateTextPos();

	std::function<void(void)> callback;
	bool toggle = false;
	bool centerOrigin;
	Text text;
	Rectangle rect;
	sf::Vector2f position;
};


#endif // !BUTTON_H


