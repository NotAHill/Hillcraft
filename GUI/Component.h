#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <iostream>

class RenderMaster;

class Component : private sf::NonCopyable
{
public:
	Component() { };
	Component(const Component& c) { std::cout << "Copy constructor called" << std::endl; }
	virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) {};
	virtual void render(RenderMaster& renderer) {};

	virtual void select() { selected = true; }
	virtual void deselect() { selected = false; }

	virtual void activate() { active = true; }
	virtual void deactivate() { active = false; }

	bool selected = false;
	bool active = false;
	bool enabled = true;

	class Text : public sf::Text
	{
	public:
		Text();
	};

	class Rectangle : public sf::RectangleShape
	{
	public:
		bool isHovered(const sf::RenderWindow& window);
		bool isClicked(const sf::Event& event, const sf::RenderWindow& window);
	};
};


#endif // !COMPONENT_H




