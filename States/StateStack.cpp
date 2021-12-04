#include "StateStack.h"
#include "BaseState.h"
#include "../Renderer/RenderMaster.h"

StateStack::StateStack() :
	stack(),
	pendingQueue()
{
}

void StateStack::pushState(std::unique_ptr<BaseState> state)
{
	pendingQueue.push_back(std::make_pair(Push, std::move(state)));
}

void StateStack::popState()
{
	pendingQueue.push_back(std::make_pair(Pop, nullptr));
}

void StateStack::clearStates()
{
	pendingQueue.push_back(std::make_pair(Clear, nullptr));
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

	applyPendingChanges();
}

void StateStack::fixedUpdate(sf::Time deltaTime)
{
	// Iterate front-to-back in the state stack
	// When fixedUpdate() return false the loop stops
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->fixedUpdate(deltaTime)) break;

	applyPendingChanges();
}

void StateStack::render(RenderMaster& renderer)
{
	// Iterate back to front in the state stack
	for (auto& state : stack)
		state->render(renderer);
}

void StateStack::handleEvent(sf::Event& event)
{
	// Iterate front-to-back in the state stack
	// When handleEvents() return false the loop stops
	for (auto itr = stack.rbegin(); itr != stack.rend(); ++itr)
		if (!(*itr)->handleEvent(event)) break;

	applyPendingChanges();
}

void StateStack::applyPendingChanges()
{
	for (auto& change : pendingQueue)
	{
		switch (change.first)
		{
		case Push:
			stack.push_back(std::move(change.second));
			break;

		case Pop:
			stack.pop_back();
			break;

		case Clear:
			stack.clear();
			break;

		case Change:
			break;
		}
	}
	pendingQueue.clear();
}
