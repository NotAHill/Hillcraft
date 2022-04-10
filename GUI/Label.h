#pragma once
#ifndef LABEL_H
#define LABEL_H

#include "Component.h"

enum class LabelSize
{
	SMALL,
	WIDE,
	ADAPTIVE
};

class Label : public Component
{
public:
	Label(LabelSize size = LabelSize::ADAPTIVE, bool centerOrigin = false);

	void render(RenderMaster& renderer);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

	void setText(const std::string& _text);
	void setPosition(const sf::Vector2f& _position);
	void setPosition(const float& x, const float& y);

	Text text;
	Rectangle rect;
};

#endif // !LABEL_H



