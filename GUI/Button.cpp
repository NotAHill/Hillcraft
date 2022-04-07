#include "Button.h"
#include "../Util/ResourceManager.h"

GUI::Button::Button()
{
	setTexture("ButtonNormal");
	text.setFont(ResourceManager::get().fonts.get("Fixedsys"));
	text.setCharacterSize(30u);
	text.setOutlineColor(sf::Color::Black);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(1.5f);

	sprite.setOrigin(sprite.getLocalBounds().width / 2,
		sprite.getLocalBounds().height / 2);

	// Centralise origin for both
	auto bounds = sprite.getLocalBounds();
	text.setPosition(bounds.width / 2.0f, bounds.height / 2.0f);

	toggleable = false;
}

void GUI::Button::setCallback(std::function<void(void)> func)
{
	function = std::move(func);
}

void GUI::Button::setText(std::string _text)
{
	text.setString(_text);
	text.setOrigin(text.getLocalBounds().width / 2,
		text.getLocalBounds().height / 2);
}

void GUI::Button::setPosition(const sf::Vector2f& pos)
{
	sprite.setPosition(pos);
	text.setPosition(pos);
	text.move(0, -10.0f);
}

void GUI::Button::setToggle(bool _toggle)
{
	toggleable = _toggle;
}

void GUI::Button::setTexture(const std::string& filename)
{
	sprite.setTexture(ResourceManager::get().textures.get(filename));
}

void GUI::Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	auto pos = sf::Mouse::getPosition(window);

	if (sprite.getGlobalBounds().contains(pos.x, pos.y) && !isDisabled())
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			activate();
		else
			select();
	}
	else 
	{
		if (isSelected())
			deselect();
	}

}

void GUI::Button::render(RenderMaster& renderer)
{
	renderer.drawSFML(sprite);
	renderer.drawSFML(text);
}

bool GUI::Button::isSelectable() const
{
	return !isDisabled();
}

void GUI::Button::select()
{
	Component::select();
	setTexture("ButtonSelected");
}

void GUI::Button::deselect()
{
	Component::deselect();
	//if (!toggleable) setTexture("ButtonNormal");
	//else
	//{
	//	if (isActivated())
	//		setTexture("ButtonPressed");
	//	else
	//		setTexture("ButtonNormal");
	//}
}

void GUI::Button::activate()
{
	Component::activate();

	if (toggleable)
		setTexture("ButtonPressed");

	function();

	if (!toggleable)
		deactivate();
}

void GUI::Button::deactivate()
{
	Component::deactivate();

	if (toggleable)
	{
		if (isSelected())
			setTexture("ButtonPressed");
		else
			setTexture("ButtonNormal");
	}
}
