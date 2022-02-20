#pragma once
#ifndef QUADRENDERER_H
#define QUADRENDERER_H

#include "../Model.h"
#include "../Util/Shader.h"
#include "../Camera.h"

#include <vector>

class Game;
class Model;

class QuadRenderer
{
public:
	QuadRenderer();
	void add(const Vector3& position);
	void render(const Camera& camera);

private:
	std::vector<Vector3> quads;
	Model quadModel;
};


#endif // !QUADRENDERER_H

