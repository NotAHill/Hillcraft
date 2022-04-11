#pragma once
#ifndef SPAWNCOMMAND_H
#define SPAWNCOMMAND_H

#include "BaseCommand.h"
#include "../Maths/glm.h"
#include "../World/World.h"

class Object;

class SpawnCommand : public BaseCommand
{
public:
	SpawnCommand(std::shared_ptr<Object> _entity, World& _world, glm::vec3& _pos, float _timer = 0.0f);

	void start();
	void update(float deltaTime);

private:
	std::shared_ptr<Object> entity;
	World* world;
	float timer;
	glm::vec3* position;
};


#endif // !SPAWNCOMMAND_H


