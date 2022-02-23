#pragma once
#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H


#include "../Model.h"
#include "../Util/Shader.h"
#include "../Camera.h"

#include <vector>

class Game;
class Model;

class TerrainRenderer
{
public:
	TerrainRenderer();
	void add(const Vector3& position);
	void render(const Camera& camera);

private:
	std::vector<Vector3> terrainList;
	Model terrainModel;
	float size;
	int vertexCount;
};



#endif // !TERRAINRENDERER_H
