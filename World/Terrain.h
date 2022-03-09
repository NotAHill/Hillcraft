#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Entities/Entity.h"
#include "../Util/Noise/FractalNoiseGenerator.h"

#include <SFML/Graphics/Image.hpp>
#include <string>
#include <memory>

class Terrain : public Entity, private sf::NonCopyable
{
public:
	Terrain(const glm::vec2& _offset, const float& _size, const unsigned int& _vertexCount, const float& _maxHeight, FractalNoiseGenerator& _noise);

	Model& getModel();
	float getHeightOfTerrain(const float& x, const float& z);
	void setVisible(const bool& _visible);
	const bool& isVisible() const;
	glm::vec2 offset;
private:
	void generateTerrain();
	float getHeight(const unsigned int& u, const unsigned int& v);
	glm::vec3 getColour(const float& height);
	glm::vec3 calculateNormal(const unsigned int& x, const unsigned int& z);


private:
	Model terrainModel;
	FractalNoiseGenerator* noise;
	std::vector<std::vector<float>> heights;

	const float size;
	const unsigned int vertexCount;
	const float maxHeight;
	bool visible;
};



#endif // !TERRAIN_H

