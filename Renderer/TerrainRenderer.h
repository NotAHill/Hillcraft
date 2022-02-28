#pragma once
#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H


#include "../Model.h"
#include "../Util/Shader.h"
#include "../Entities/Camera.h"
#include "../World/Light.h"
#include "../World/Terrain.h"

#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <memory>

class Game;

class TerrainRenderer
{
public:
	TerrainRenderer();
	void render(const Camera& camera, std::vector<Terrain> terrains, std::vector<Light> lights);

private:
	
};



#endif // !TERRAINRENDERER_H
