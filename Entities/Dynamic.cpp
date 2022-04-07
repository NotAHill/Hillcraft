#include "Dynamic.h"

Dynamic::Dynamic(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	Object(_model, _position, _rotation, _scale),
	baseDamage(0)
{
}

Dynamic::~Dynamic()
{
}
