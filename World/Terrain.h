#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "../Model/Model.h"
#include "../Maths/glm.h"
#include "../Entities/Entity.h"
#include "../Entities/Object.h"
#include "../Util/Noise/FractalNoiseGenerator.h"
#include "../Model/TexturedModel.h"

#include <SFML/Graphics/Image.hpp>
#include <string>
#include <memory>
#include <unordered_map>

class Terrain : public Entity, private sf::NonCopyable
{
public:
	Terrain(const glm::vec2& _offset, const float& _size, const unsigned int& _vertexCount, const float& _maxHeight, FractalNoiseGenerator& _noise, std::unordered_map<std::string, std::shared_ptr<TexturedModel>>& modelMap);

	Model& getModel();
	float getHeightOfTerrain(const float& x, const float& z);
	void setVisible(const bool& _visible);
	const bool& isVisible() const;
	const std::vector<std::shared_ptr<Object>>& getObjects() const;

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
	
	// TEMP
	std::vector<std::shared_ptr<Object>> objects;

	const float size;
	const unsigned int vertexCount;
	const float maxHeight;
	bool visible;
};



#endif // !TERRAIN_H

