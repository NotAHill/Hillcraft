#pragma once

#include "Object.h"

class Player;

class Friendly : public Object
{
public:
	Friendly(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale);
	
	void update(float deltaTime, Player& player);
	void interact();
private:

};

