#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <functional>

namespace GUI
{
class Button : public Component
{
public:
	Button();

	void setCallback(std::function<void(void)> func);
	void setText(std::string _text);
	void setPosition(const sf::Vector2f& pos);
	void setToggle(bool _toggle);
	void setTexture(const std::string& filename);

	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void render(RenderMaster& renderer);

	bool isSelectable() const;

	void select();
	void deselect();

	void activate();
	void deactivate();

private:
	std::function<void(void)> function;

	sf::Text text;
	sf::Sprite sprite;

	bool toggleable;
};

}
#endif // !BUTTON_H



