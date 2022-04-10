#include "Friendly.h"

Friendly::Friendly(TexturedModel& _model, glm::vec3 _position, glm::vec3 _rotation, float _scale) :
	Object(_model, _position, _rotation, _scale)
{
}

void Friendly::update(float deltaTime, Player& player)
{
}

void Friendly::interact()
{
	static int counter = 0;
	std::cout << "I have been pressed: " <<  ++counter << " times" << std::endl;
}
