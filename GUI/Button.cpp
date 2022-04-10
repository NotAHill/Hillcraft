#include "Button.h"

#include "../Renderer/RenderMaster.h"

Button::Button(ButtonSize size, bool _centerOrigin)
{
	selected = false;
	enabled = true;
	active = false;
	centerOrigin = _centerOrigin;

	rect.setOutlineThickness(-3.0f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::Blue);

	switch (size)
	{
	case ButtonSize::XSMALL:
		rect.setSize({ 300.0f / 3.0f, 64 });
		break;

	case ButtonSize::SMALL:
		rect.setSize({ 300.0f / 2.0f, 64 });
		break;

	case ButtonSize::WIDE:
		rect.setSize({ 300, 64 });
		break;
	}

	// Center the origin of the rectangle to its center
	if (centerOrigin)
		rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	if (rect.isHovered(window))
	{
		select();

		if (rect.isClicked(event, window))
		{
			activate();
		}
	}
	else
	{
		deselect();
	}
}

void Button::render(RenderMaster& renderer)
{
	renderer.drawSFML(rect);
	renderer.drawSFML(text);
}

void Button::setCallback(std::function<void(void)> _callback)
{
	// Maybe not std move
	callback = std::move(_callback);
}

void Button::setText(const std::string& _text)
{
	text.setString(_text);

	// Center the text
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

void Button::setToggle(const bool& _toggle)
{
	toggle = _toggle;
}

void Button::setPosition(const float& x, const float& y)
{
	setPosition({ x, y });
}

void Button::setPosition(const sf::Vector2f& _position)
{
	position = _position;

	rect.setPosition(position);
	text.setPosition(position);
	
	if (!centerOrigin)
		text.move(rect.getLocalBounds().width / 2.0f, rect.getLocalBounds().height / 2.0f);
	text.move(0, -10.0f);
}

void Button::select()
{
	Component::select();

	rect.setOutlineColor(sf::Color::Yellow);
}

void Button::deselect()
{
	Component::deselect();

	//if (active) rect.setOutlineColor(sf::Color::Red);
	//else rect.setOutlineColor(sf::Color::Black);

	rect.setOutlineColor(sf::Color::Black);
}

void Button::activate()
{
	//Component::activate();
	active = !active;

	if (active) rect.setFillColor({ 0, 0, 200 });
	else rect.setFillColor(sf::Color::Blue);

	callback();

	if (!toggle)
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();
	rect.setFillColor(sf::Color::Blue);
}

sf::Vector2f Button::getPosition() const
{
	return position;
}

sf::Vector2f Button::getSize() const
{
	return { rect.getGlobalBounds().width, rect.getGlobalBounds().height };
}

void Button::updateTextPos()
{
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.move(rect.getGlobalBounds().width / 2, rect.getGlobalBounds().height / 2.5f);
}
