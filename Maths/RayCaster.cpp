#include "RayCaster.h"

RayCaster::RayCaster(const glm::vec3& _position, const glm::vec3& _direction) :
	start(_position),
	end(_position),
	direction(_direction)
{
}

void RayCaster::step(float scale)
{
	float yaw = glm::radians(direction.y + 90);
	float pitch = glm::radians(direction.x);

	end.x -= glm::cos(yaw) * scale;
	end.z -= glm::sin(yaw) * scale;
	end.y -= glm::tan(pitch) * scale;
}

glm::vec3 RayCaster::getEnd() const
{
	return end;
}

float RayCaster::getLength() const
{
	return glm::distance(start, end);
}
