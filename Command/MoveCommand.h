#pragma once
#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "BaseCommand.h"
#include "../Maths/glm.h"

#include "../Entities/Entity.h"

class MoveCommand : public BaseCommand
{
public:
	MoveCommand(Entity& _entity, const glm::vec3& _targetPos, float _duration = 0.0f, bool enableFlight = false);
	void start();
	void update(float deltaTime);

private:
	Entity* entity;

	glm::vec3 startPos;
	glm::vec3 targetPos;
	float duration;
	float elapsedTime;
	bool flight;
};

#endif // !MOVE_COMMAND_H



