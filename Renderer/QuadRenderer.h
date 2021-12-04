#pragma once
#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "../Model.h"
#include "../Util/Shader.h"

#include <vector>

class Game;
class Model;

class QuadRenderer
{
public:
	QuadRenderer(Game& game);

	void add(const Vector3& position);
	void render();

private:
	std::vector<Vector3> quads;

	Model quadModel;
	Game* gamePtr;
};


#endif // !QUADRENDERER_H

