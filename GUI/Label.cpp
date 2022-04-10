#include "Label.h"

#include "../Renderer/RenderMaster.h"

Label::Label(LabelSize size, bool centerOrigin)
{
	// Readonly therefore set all to false
	selected = false;
	active = false;
	enabled = false;

	rect.setOutlineThickness(3.0f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::White);
}

void Label::render(RenderMaster& renderer)
{
	renderer.drawSFML(rect);
	renderer.drawSFML(text);
}

void Label::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	// Nothing happens
}

void Label::setText(const std::string& _text)
{
	std::string buffer = _text;
	for (auto& letter : _text)
	{
		buffer += letter;
		//if (text)
		text.setString(buffer);
	}
}

void Label::setPosition(const sf::Vector2f& _position)
{
	rect.setPosition(_position);
	text.setPosition(_position);
}

void Label::setPosition(const float& x, const float& y)
{
	setPosition({ x, y });
}
