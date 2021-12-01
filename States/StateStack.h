#pragma once
#ifndef STATESTACK_H
#define STATESTACK_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <memory>

class BaseState;

class StateStack : private sf::NonCopyable
{
public:
	StateStack();

	// State is pushed into stack
	template<typename State, typename... Args>
	void pushState(Args&&... args)
	{ stack.push_back(std::make_unique<State>(std::forward<Args>(args)...)); }

	//void pushState(std::unique_ptr<BaseState> state)
	//{
	//	stack.push_back(state); // std::move() ???
	//}

	void popState();
	void clearStates();
	BaseState& getCurrentState() const;

	const bool& isEmpty() const;

	void update(sf::Time deltaTime);
	void fixedUpdate(sf::Time deltaTime);
	void render(sf::RenderTarget& target);
	void handleEvent(sf::Event& event);
	
private:
	std::vector<std::unique_ptr<BaseState>> stack;
};



#endif // !STATESTACK_H
