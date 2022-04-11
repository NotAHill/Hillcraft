#pragma once
#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include "BaseCommand.h"

#include <queue>
#include <memory>

class ScriptEngine
{
public:
	ScriptEngine();

	void addCommand(std::unique_ptr<BaseCommand> command);
	void processCommands(float deltaTime);
	void finishCommand();
	const bool& isEmpty() const;

private:
	std::queue<std::unique_ptr<BaseCommand>> commandQueue;
};


#endif // !SCRIPT_ENGINE_H


