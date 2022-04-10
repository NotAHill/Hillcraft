#include "DialogueCommand.h"

#include "../States/GameState.h"

DialogueCommand::DialogueCommand(GameState& state, std::vector<std::string> _lines) :
	gameState(&state),
	lines(_lines)
{
	timer = 10.0f;
}

void DialogueCommand::start()
{
	gameState->addDialogue(lines);
}

void DialogueCommand::update(float deltaTime)
{
	timer -= deltaTime;
	if (timer <= 0.0f)
	{
		finished = true;
	}
}
