#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "Entity.h"
#include "../TexturedModel.h"

#include <SFML/Graphics/Texture.hpp>

class Object : public Entity
{
public:
	Object(const TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale);

	Texture& getTexture();
	TexturedModel& getModel() const;

private:
	// make unique ptr instead
	TexturedModel model;
	Texture texture;
};



#endif // !OBJECT_H

