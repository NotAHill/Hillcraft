#include "MoveCommand.h"


MoveCommand::MoveCommand(Entity& _entity, const glm::vec3& _targetPos, float _duration, bool enableFlight) :
	entity(&_entity),
	targetPos(_targetPos),
	duration(std::max(_duration, 0.01f)),
	flight(enableFlight),
	elapsedTime(0.0f)
{
}

void MoveCommand::start()
{
	startPos = entity->position;
}

void MoveCommand::update(float deltaTime)
{
	elapsedTime += deltaTime;
	float t = elapsedTime / duration;
	if (t > 1.0f) t = 1.0f;

	auto lerp = [&](float start, float end, float a)
	{
		return (end - start) * a + start;
	};

	entity->position.x = lerp(startPos.x, targetPos.x, t);
	entity->position.z = lerp(startPos.z, targetPos.z, t);

	if (flight)
		entity->position.y = lerp(startPos.y, targetPos.y, t);

	if (elapsedTime >= duration)
	{
		entity->velocity.y = 0.0f;
		
		entity->position.x = targetPos.x;
		entity->position.z = targetPos.z;

		if (flight)
			entity->position.y = targetPos.y;

		finished = true;
	}

}
