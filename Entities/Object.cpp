#include "Object.h"

Object::Object(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	model(&_model)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;
}

TexturedModel* Object::getModel() const
{
	return model;
}
