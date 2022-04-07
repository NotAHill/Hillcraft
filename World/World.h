#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "../Config.h"								// Global variables
#include "../Util/Noise/FractalNoiseGenerator.h"	// Height/Colour generation
#include "../Entities/Camera.h"						// Camera class
#include "Terrain.h"								// Terrain/Chunk
#include "../Entities/Dynamic.h"

#include <unordered_map>							// Chunk dictionary
#include <memory>									// Unique pointer

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
	void updateChunks(float deltaTime, Dynamic& player);

	std::shared_ptr<Terrain> getCurrentChunk() const;
	std::shared_ptr<Terrain> getChunk(const Entity& entity) const;

	std::vector<std::shared_ptr<Terrain>>& getLoadedChunks();
	std::vector<std::shared_ptr<Object>>& getLoadedObjects();
	std::vector<std::shared_ptr<Dynamic>>& getLoadedDynamics();
private:
	// Maybe unnecessary
	int visibleChunks;

	
	std::unordered_map<glm::vec2, std::shared_ptr<Terrain>> chunkMap;			// Contains all the chunks
	std::unordered_map<std::string , std::shared_ptr<TexturedModel>> modelMap;	// Contains all the textured models

	
	std::vector<std::shared_ptr<Terrain>> chunksPreviousUpdate;	// Contains all the rendered chunks/objects for drawing
	std::vector<std::shared_ptr<Object>> objectsPreviousUpdate;
	std::vector<std::shared_ptr<Dynamics>> ;
	
	std::shared_ptr<Terrain> currentChunk;// For height calculation

	
	FractalNoiseGenerator heightGen;	// Procedural generation
	//FractalNoiseGenerator colourGen;

};

#endif // !WORLD_H



