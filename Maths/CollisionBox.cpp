#include "CollisionBox.h"

bool CollisionBox::isPointInBox(const glm::vec3& point)
{
    return glm::distance(point, position) < radius;
}
