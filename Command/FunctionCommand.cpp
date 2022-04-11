#include "FunctionCommand.h"

FunctionCommand::FunctionCommand(std::function<void(void)> _function = []() {}, float _timer)
{
	function = std::move(_function);
	timer = _timer;
}

void FunctionCommand::start()
{
	function();
}

void FunctionCommand::update(float deltaTime)
{
	timer -= deltaTime;
	if (timer <= 0.0f) finished = true;
}
