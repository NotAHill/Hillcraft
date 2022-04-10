#pragma once
#ifndef LABEL_H
#define LABEL_H

#include "Component.h"

class Label : public Component
{
public:
	Label(bool _centerOrigin = false, float _timer = INFINITY);

	void render(RenderMaster& renderer);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

	void setText(const std::vector<std::string>& _text);
	void setPosition(const sf::Vector2f& _position);
	void setPosition(const float& x, const float& y);

	Text text;
	Rectangle rect;
	bool centerOrigin;
	float timer;
	sf::Clock clock;
};

#endif // !LABEL_H



