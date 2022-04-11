#include "DialogueCommand.h"

#include "../States/GameState.h"

DialogueCommand::DialogueCommand(GameState& state, std::vector<std::string> _lines) :
	gameState(&state),
	lines(_lines)
{
	timer = 3.0f;
}

void DialogueCommand::start()
{
	gameState->addDialogue(lines, timer);
}

void DialogueCommand::update(float deltaTime)
{
	timer -= deltaTime;
	if (timer <= 0.0f)
	{
		finished = true;
	}
}
