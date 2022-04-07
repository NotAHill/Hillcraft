#include "Component.h"

bool GUI::Component::isDisabled() const
{
	return disabled;
}

void GUI::Component::disable()
{
	disabled = true;
}

void GUI::Component::enable()
{
	disabled = false;
}

bool GUI::Component::isSelected() const
{
	return isSelected();
}

void GUI::Component::select()
{
	selected = true;
}

void GUI::Component::deselect()
{
	selected = false;
}

bool GUI::Component::isActivated() const
{
	return active;
}

void GUI::Component::activate()
{
	active = true;
}

void GUI::Component::deactivate()
{
	active = false;
}
