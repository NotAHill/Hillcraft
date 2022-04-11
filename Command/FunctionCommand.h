#pragma once
#ifndef FUNCTION_COMMAND_H
#define FUNCTION_COMMAND_H

#include "BaseCommand.h"

#include <functional>

class FunctionCommand : public BaseCommand
{
public:
	FunctionCommand(std::function<void(void)> _function, float _timer = 0.0f);

	void start();
	void update(float deltaTime);

private:
	std::function<void(void)> function;
	float timer;
};


#endif // !FUNCTION_COMMAND_H
