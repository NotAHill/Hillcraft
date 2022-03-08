#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Config.h"		// Global variables
#include "Util/Noise/FractalNoiseGenerator.h"	// Height/Colour generation
#include "Entities/Camera.h"	// Camera class
#include "World/Terrain.h" // Terrain/Chunk

#include <unordered_map> // Chunk dictionary
#include <memory>	// Unique pointer

class World
{
public:
	World();
	void updateChunks(const Camera& camera);
	std::unique_ptr<Terrain> getCurrentChunk() const;

private:
	int visibleChunks;
	std::unordered_map<glm::vec2, std::unique_ptr<Terrain>> chunkMap;
	std::vector<std::unique_ptr<Terrain>> chunksPreviousUpdate;

	// Maybe try shared ptr
	std::unique_ptr<Terrain> currentChunk;
	FractalNoiseGenerator heightGen;
	FractalNoiseGenerator colourGen;

};

#endif // !WORLD_H



