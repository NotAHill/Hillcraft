#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "DynamicCreature.h"

class Enemy : public DynamicCreature
{
public:
	Enemy(TexturedModel& _model, glm::vec3 _position = { 0, 0, 0 }, glm::vec3 _rotation = { 0, 0, 0 }, float _scale = 1.0f);
	~Enemy();

	void behaviour();
	void attack();
	void update(float deltaTime, Dynamic& player);
private:

};

#endif // !ENEMY_H



