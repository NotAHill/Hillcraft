#pragma once
#ifndef DIALOGUE_COMMAND_H
#define DIALOGUE_COMMAND_H

#include "BaseCommand.h"

#include <vector>
#include <string>

class GameState;

class DialogueCommand : public BaseCommand
{
public:
	DialogueCommand(GameState& state, std::vector<std::string> _lines);
	void start();
	void update(float deltaTime);

private:
	GameState* gameState;
	std::vector<std::string> lines;
	float timer;
};


#endif // !DIALOGUE_COMMAND_H



