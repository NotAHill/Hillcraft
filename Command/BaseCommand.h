#pragma once
#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

//class Game;

class BaseCommand
{
public:
	//BaseCommand(Game& game);
	virtual ~BaseCommand();

	virtual void start() = 0;
	virtual void update(float deltaTime) = 0;

	// No need for getters and setters
	bool started = false;
	bool finished = false;
//protected:
	//Game* gamePtr;


};


#endif // !BASE_COMMAND_H


