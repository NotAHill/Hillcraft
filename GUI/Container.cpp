#include "Container.h"

Container::Container()
{
	selectedComponent = -1;

	enabled = false;
	selected = true;
	active = true;
}

void Container::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	// Mouse input
	for (std::size_t i = 0; i < components.size(); ++i)
	{
		components[i]->handleEvent(event, window);
		if (components[i]->selected)
		{
			selectedComponent = i; // maybe break?
			return;
		}
	}

	// Keyboard Input
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
			{
				components[selectedComponent]->activate();
			}
		}
	}
}

void Container::render(RenderMaster& renderer)
{	
	//components.erase(std::remove_if(components.begin(), components.end(), [](std::shared_ptr<Component> c) { return !c->enabled; }), components.end());
	for (auto& component : components)
		component->render(renderer);
}

void Container::addComponent(std::shared_ptr<Component> component)
{
	bool temp = component->enabled;
	components.push_back(component);

	// If no component is already selected then select the last component (i.e the one just added)
	if (!hasSelection() && temp)
		select(components.size() - 1);
}

const bool& Container::hasSelection()
{
	// Maybe adjust hasSelection() by iterating through all components for mouse support?
	return selectedComponent >= 0;
}

void Container::select(const std::size_t& index)
{
	if (components[index]->enabled)
	{
		// Deselect the previously selected component
		if (hasSelection())
			components[selectedComponent]->deselect();

		// Select the new component
		components[index]->select();
		selectedComponent = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Choose the next enabled component
	// Wrap around if necessary
	int next = selectedComponent;
	do
		next = (next + 1) % components.size();
	while (!components[next]->enabled);

	// Select the component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Choose the prev enabled component
	// Wrap around if necessary
	int prev = selectedComponent;
	do
		prev = (prev + components.size() - 1) % components.size();
	while (!components[prev]->enabled);

	// Select the component
	select(prev);
}
