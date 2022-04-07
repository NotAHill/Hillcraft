#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include "../Renderer/RenderMaster.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace GUI
{

class Component : private sf::NonCopyable
{
public:
	virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
	virtual void render(RenderMaster& renderer) = 0;

	virtual bool isSelectable() const = 0;

	bool isDisabled() const;
	virtual void disable();
	virtual void enable();

	bool isSelected() const;
	virtual void select();
	virtual void deselect();

	bool isActivated() const;
	virtual void activate();
	virtual void deactivate();

private:
	bool selected = false;
	bool active = false;
	bool disabled = false;
};

}

#endif // !COMPONENT_H


