#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Dynamic.h"

class Projectile : public Dynamic
{
public:
	Projectile(TexturedModel& _model, glm::vec3 _origin, glm::vec3 _velocity, bool _friendly, float _duration);

private:
	bool oneHit = true;
	float duration;
};


#endif // !PROJECTILE_H



