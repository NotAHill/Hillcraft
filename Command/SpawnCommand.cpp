#include "SpawnCommand.h"

#include "../Entities/Object.h"
#include "../Entities/Friendly.h"
#include "../Entities/Enemy.h"

#include <memory>

SpawnCommand::SpawnCommand(std::shared_ptr<Object> _entity, World& _world, glm::vec3& _pos, float _timer)
{
	entity = std::move(_entity);
	world = &_world;
	timer = _timer;
	position = &_pos;
}

void SpawnCommand::start()
{
	auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
	auto friendly = std::dynamic_pointer_cast<Friendly>(entity);

	if (position == nullptr)
		position = &entity->position;
	else
		entity->position = *position;

	if (enemy)
	{
		world->getChunkAt(position->x, position->z)->getEnemies().push_back(enemy);
		std::cout << "Enemy added" << std::endl;
	}
	else if (friendly)
	{
		world->getChunkAt(position->x, position->z)->getFriendlies().push_back(friendly);
		friendly->box.position = friendly->position;
		std::cout << "Friendly added" << std::endl;
	}
	else				world->getChunkAt(position->x, position->z)->getObjects().push_back(entity);
}

void SpawnCommand::update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f) finished = true;
}
