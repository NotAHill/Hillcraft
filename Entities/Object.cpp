#include "Object.h"

Object::Object(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	model(&_model),
	box(3.0f)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;

	box.update(position);
}

TexturedModel* Object::getModel() const
{
	return model;
}
