#include "StateStack.h"
#include "BaseState.h"

StateStack::StateStack() :
	stack()
{
}

void StateStack::popState()
{
	stack.pop_back();
}

void StateStack::clearStates()
{
	stack.clear();
}

BaseState& StateStack::getCurrentState() const
{
	return *stack.back();
}

const bool& StateStack::isEmpty() const
{
	return stack.empty();
}

void StateStack::update(sf::Time deltaTime)
{
	// Iterate front-to-back in the state stack
	// When update() return false the loop stops
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->update(deltaTime)) break;
}

void StateStack::fixedUpdate(sf::Time deltaTime)
{
	// Iterate front-to-back in the state stack
	// When fixedUpdate() return false the loop stops
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->fixedUpdate(deltaTime)) break;
}

void StateStack::render(sf::RenderTarget& target)
{
	// Iterate back to front in the state stack
	for (auto& state : stack)
		state->render(target);
}

void StateStack::handleEvent(sf::Event& event)
{
	// Iterate front-to-back in the state stack
	// When handleEvents() return false the loop stops
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->handleEvent(event)) break;
}
