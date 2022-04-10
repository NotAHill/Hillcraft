#include "Label.h"

#include "../Renderer/RenderMaster.h"

Label::Label(bool _centerOrigin, float _timer)
{
	// Readonly therefore set all to false
	selected = false;
	active = false;
	enabled = false;
	centerOrigin = _centerOrigin;
	timer = _timer;
	
	rect.setOutlineThickness(3.0f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::Blue);

	
	if (centerOrigin)
		rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
}

void Label::render(RenderMaster& renderer)
{
	if (clock.getElapsedTime().asSeconds() < timer)
	{
		renderer.drawSFML(rect);
		renderer.drawSFML(text);
	}
}

void Label::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	// Nothing happens
}

void Label::setText(const std::vector<std::string>& _text)
{
	std::string buffer;
	for (int line = 0; line < _text.size(); line++)
		buffer += _text[line] + "\n";

	text.setString(buffer);
	rect.setSize({ text.getLocalBounds().width * 1.05f + 10.0f, text.getLocalBounds().height });

	if (centerOrigin)
		rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
}

void Label::setPosition(const sf::Vector2f& _position)
{
	rect.setPosition(_position);
	text.setPosition(_position);

	if (centerOrigin)
		text.move(-rect.getLocalBounds().width / 2.2f, -rect.getLocalBounds().height / 2.5f);
	else
		text.move(10.0f, 0.0f);
}

void Label::setPosition(const float& x, const float& y)
{
	setPosition({ x, y });
}
