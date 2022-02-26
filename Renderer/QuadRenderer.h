#pragma once
#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "../Model.h"
#include "../Util/Shader.h"
#include "../Entities/Camera.h"

#include <vector>

class Game;
class Model;

class QuadRenderer
{
public:
	QuadRenderer();
	void add(const Vector3& position, const Vector3& rotation);
	void render(const Camera& camera);

private:
	std::vector<Entity> quads;
	Model quadModel;
};


#endif // !QUADRENDERER_H

