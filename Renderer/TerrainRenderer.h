#pragma once
#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H


#include "../Model.h"
#include "../Util/Shader.h"
#include "../Camera.h"

#include <vector>
#include <SFML/Graphics/Image.hpp>

class Game;
class Model;

class TerrainRenderer
{
public:
	TerrainRenderer();
	void add(const Vector3& position, const Vector3& rotation);
	void render(const Camera& camera);

private:
	float getHeight(const unsigned int& u, const unsigned int& v, const sf::Image& image, const unsigned int& stepSize);
	glm::vec3 getColour(const float& height);
	glm::vec3 calculateNormal(const unsigned int& x, const unsigned int& z, const sf::Image& image, const unsigned int& stepSize);

	std::vector<Entity> terrainList;
	Model terrainModel;
	
	int vertexCount;
	float size;
	float maxHeight;
};



#endif // !TERRAINRENDERER_H
