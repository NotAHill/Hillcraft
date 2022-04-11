#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"

#include <memory>

class Container : public Component
{
public:
	Container();

	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void render(RenderMaster& renderer);

	void addComponent(std::shared_ptr<Component> component);

	std::shared_ptr<Component> operator[] (const std::size_t& i) { return components[i]; }

protected:
	const bool& hasSelection();
	
	void select(const std::size_t& index);
	void selectNext();
	void selectPrevious();

	std::vector<std::shared_ptr<Component>> components;
	int selectedComponent;
};

#endif // !CONTAINER_H



