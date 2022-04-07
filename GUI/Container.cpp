#include "Container.h"

GUI::Container::Container() :
	nodePointer(-1)
{
}

void GUI::Container::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);

	if (hasSelection() && component->isSelectable())
		select(components.size() - 1);
}

void GUI::Container::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	for (auto& component : components)
	{
		component->handleEvent(event, window);
	}
	
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			selectPrevious();
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			selectNext();
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			if (hasSelection())
				components[nodePointer]->activate();
	}
}

void GUI::Container::render(RenderMaster& renderer)
{
	for (auto& component : components)
	{
		component->render(renderer);
	}
}

bool GUI::Container::isSelectable() const
{
	return false;
}

bool GUI::Container::hasSelection() const
{
	return nodePointer >= 0;
}

void GUI::Container::select(const std::size_t& index)
{
	if (components[index]->isSelectable())
	{
		if (hasSelection())
			components[nodePointer]->deselect();

		components[index]->select();
		nodePointer = index;
	}
}

void GUI::Container::selectNext()
{
	if (!hasSelection()) return;

	int next = nodePointer;
	do
		next = (next + 1) % components.size();
	while (!components[nodePointer]->isSelectable());

	select(next);
}

void GUI::Container::selectPrevious()
{
	if (!hasSelection()) return;

	int prev = nodePointer;
	do
		prev = (prev + components.size() - 1) % components.size();
	while (!components[nodePointer]->isSelectable());

	select(prev);
}
