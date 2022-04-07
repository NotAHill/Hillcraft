#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "Component.h"
#include "../Renderer/RenderMaster.h"

namespace GUI
{

class Container : public Component
{
public:
	Container();

	void addComponent(std::shared_ptr<Component> component);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
	void render(RenderMaster& renderer);

	bool isSelectable() const;

private:
	bool hasSelection() const;

	void select(const std::size_t& index);
	void selectNext();
	void selectPrevious();

	std::vector<std::shared_ptr<Component>> components;
	int nodePointer;
};

}

#endif // !CONTAINER_H



