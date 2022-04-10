#include "Textbox.h"

#include "../Renderer/RenderMaster.h"

Textbox::Textbox(TextboxSize size)
{
	selected = false;
	enabled = true;
	active = false;

	rect.setOutlineThickness(3.0f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::White);

	switch (size)
	{
	case TextboxSize::SMALL:
		rect.setSize({ 300 / 2, 50 });
		break;

	case TextboxSize::WIDE:
		rect.setSize({ 300, 50 });
		break;
	}

	// Center the origin of the rectangle to its center
	rect.setOrigin(rect.getLocalBounds().width / 2, rect.getLocalBounds().height / 2);
}

void Textbox::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))
		deselect();
	// Mouse events
	else if (rect.isHovered(window))
	{
		if (rect.isClicked(event, window))
		{
			select();
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
		deselect();

	auto isValidChar = [](unsigned char code)
	{
		return (code >= 46 && code <= 57) ||  // Numbers
			   (code >= 65 && code <= 90) ||  // Uppercase
			   (code >= 97 && code <= 122)||  // Lowercase
			   (code == 32) || (code == 92);  // Space/Dot
	};

	// Keyboard events
	if (event.type == sf::Event::TextEntered)
	{
		if (selected)
		{
			unsigned char keyCode = event.text.unicode;

			// Enter
			if (keyCode == '\r')
			{
				activate();
			}
			// Backspace
			else if (keyCode == '\b')
			{
				if (textBuffer.size() > 0)
				{
					textBuffer.pop_back();
				}
			}
			else if (isValidChar(keyCode))
			{
				if (text.getGlobalBounds().width + 30 <=
					rect.getGlobalBounds().width)
					textBuffer.push_back(keyCode);
			}

			text.setString(textBuffer);
		}
	}
}

void Textbox::render(RenderMaster& renderer)
{
	renderer.drawSFML(rect);
	renderer.drawSFML(text);
}

void Textbox::select()
{
	Component::select();

	rect.setOutlineColor(sf::Color::Yellow);
}

void Textbox::deselect()
{
	Component::deselect();

	rect.setOutlineColor(sf::Color::Black);
}

void Textbox::activate()
{
	Component::activate();

	onEnter(textBuffer);
	textBuffer.clear();

	deactivate();
}

void Textbox::deactivate()
{
	Component::deactivate();
}

void Textbox::setCallback(std::function<void(const std::string&)> _callback)
{
	onEnter = std::move(_callback);
}

void Textbox::setPosition(const float& x, const float& y)
{
	setPosition({ x, y });
}

void Textbox::setPosition(const sf::Vector2f& _position)
{
	rect.setPosition(_position);
	text.setPosition(_position);
	text.move(-rect.getLocalBounds().width / 2.2f, -rect.getLocalBounds().height / 2.5f);
}
