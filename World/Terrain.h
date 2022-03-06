#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Entities/Entity.h"
#include "../Util/Noise/FractalNoiseGenerator.h"

#include <SFML/Graphics/Image.hpp>
#include <string>

class Terrain : public Entity, private sf::NonCopyable
{
public:
	Terrain(const float& _maxHeight, const float& _size, const unsigned int& _vertexCount, glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 });

	Model& getModel();
	float getHeightOfTerrain(const float& x, const float& z);

private:
	void generateTerrain(std::string heightmapLocation);
	float getHeightImg(const unsigned int& u, const unsigned int& v, const sf::Image& image);
	float getHeight(const unsigned int& u, const unsigned int& v);

	glm::vec3 getColour(const float& height);
	glm::vec3 calculateNormal(const unsigned int& x, const unsigned int& z, const sf::Image& image);

private:
	Model terrainModel;

	// Constant attributes
	const float maxHeight;
	const float size;
	const unsigned int vertexCount;

	float stepSize;
	std::vector<std::vector<float>> heights;
	FractalNoiseGenerator noise;
};



#endif // !TERRAIN_H

