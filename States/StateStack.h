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

	template<typename State, typename... Args>
	void pushState(Args&&... args)
	{ pushState(std::make_unique<State>(std::forward<Args>(args)...)); }

	void pushState(std::unique_ptr<BaseState> state);
	void popState();
	void clearStates();
	BaseState& getCurrentState() const;

	const bool& isEmpty() const;

	void update(sf::Time deltaTime);
	void fixedUpdate(sf::Time deltaTime);
	void render(sf::RenderTarget& target);
	void handleEvent(sf::Event& event);
	

private:	
	enum Action
	{
		Push,
		Pop,
		Change,
		Clear
	};

	std::vector<std::unique_ptr<BaseState>> stack;
	std::vector<std::pair<Action, std::unique_ptr<BaseState>>> pendingQueue;

	void applyPendingChanges();
};



#endif // !STATESTACK_H
