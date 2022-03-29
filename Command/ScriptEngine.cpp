#include "ScriptEngine.h"


ScriptEngine::ScriptEngine()
{
}

void ScriptEngine::addCommand(std::unique_ptr<BaseCommand> command)
{
	commandQueue.push(std::move(command));
}

void ScriptEngine::processCommands(float deltaTime)
{
	// Check if queue is not empty
	if (!commandQueue.empty())
	{
		// Check if command has finished
		if (!commandQueue.front()->finished)
		{
			// Check if command has started
			if (!commandQueue.front()->started)
			{
				// Start the command
				commandQueue.front()->start();
				commandQueue.front()->started = true;
			}
			else
			{
				// Update the ongoing command
				commandQueue.front()->update(deltaTime);
			}
		}
		else
		{
			// Remove the finished command from queue
			commandQueue.pop();
		}
	}
}

void ScriptEngine::finishCommand()
{
	if (!commandQueue.empty())
	{
		commandQueue.front()->finished = true;
	}
}
