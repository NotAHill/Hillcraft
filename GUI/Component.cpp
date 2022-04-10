#include "Component.h"

#include "../Util/ResourceManager.h"

Component::Text::Text()
{
	setFont(ResourceManager::get().fonts.get("Fixedsys"));
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(2.0f);
	setFillColor(sf::Color::White);
}

bool Component::Rectangle::isHovered(const sf::RenderWindow& window)
{
	const auto& mouse = sf::Mouse::getPosition(window);
	return getGlobalBounds().contains((float)mouse.x, (float)mouse.y);
}

bool Component::Rectangle::isClicked(const sf::Event& event, const sf::RenderWindow& window)
{
	if (isHovered(window))
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			return event.mouseButton.button == sf::Mouse::Left;
		}
	}

	return false;
}
