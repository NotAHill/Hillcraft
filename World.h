#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Config.h"		// Global variables
#include "Util/Noise/FractalNoiseGenerator.h"	// Height/Colour generation
#include "Entities/Camera.h"	// Camera class
#include "World/Terrain.h" // Terrain/Chunk

#include <unordered_map> // Chunk dictionary
#include <memory>	// Unique pointer
#include <map>

template<>
struct std::hash<glm::vec2>
{
	std::size_t operator()(const glm::vec2& vec) const noexcept
	{
		std::size_t h1 = std::hash<decltype(vec.x)>{}(vec.x);
		std::size_t h2 = std::hash<decltype(vec.x)>{}(vec.y);
		return h1 ^ (h2 << 1);
	}
};

class World
{
public:
	World();
	void updateChunks(const Entity& entity);

	std::shared_ptr<Terrain> getCurrentChunk() const;

	std::vector<std::shared_ptr<Terrain>>& getLoadedChunks();
	std::vector<std::shared_ptr<Object>>& getLoadedObjects();

private:
	// Maybe unnecessary
	int visibleChunks;

	// Contains all the chunks
	std::unordered_map<glm::vec2, std::shared_ptr<Terrain>> chunkMap;

	// Contains all the textured models
	std::unordered_map<std::string , std::shared_ptr<TexturedModel>> modelMap;

	// Contains all the rendered chunks/objects for drawing
	std::vector<std::shared_ptr<Terrain>> chunksPreviousUpdate;
	std::vector<std::shared_ptr<Object>> objectsPreviousUpdate;

	// For height calculation
	std::shared_ptr<Terrain> currentChunk;

	// Procedural generation
	FractalNoiseGenerator heightGen;
	//FractalNoiseGenerator colourGen;

};

#endif // !WORLD_H



