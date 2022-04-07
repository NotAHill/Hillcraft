#include "World.h"
#include "../Util/Statistics.h"

#include <iostream>
#include <string>

World::World() :
	heightGen(Config::SCALE, Config::OCTAVES, Config::PERSISTANCE, Config::LACUNARITY, 1), //colourGen(20.4f, 4, 0.5f, 2.0f),
	chunkMap(),
	modelMap(),
	chunksPreviousUpdate(),
	objectsPreviousUpdate()
{
	// Maximum possible chunks seen in any direction
	visibleChunks = Config::RENDER_DISTANCE;

	// Load models before chunks
	modelMap["rock"] = std::make_shared<TexturedModel>("toonRocks", "rock");
	modelMap["tree"] = std::make_shared<TexturedModel>("tree", "tree");
	modelMap["sphere"] = std::make_shared<TexturedModel>("sphere", "rock");

	chunkMap[{0, 0}] = std::make_shared<Terrain>(glm::vec2{ 0,0 }, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen, modelMap);
}

void World::updateChunks(float deltaTime, Dynamic& player)
{
	bool oneChunkPerFrame = true;

	// Reset the previous frame's chunks (Maybe unnecessary)
	for (auto& chunk : chunksPreviousUpdate)
		chunk->setVisible(false);

	// Clear all the previous frames objects/chunks
	chunksPreviousUpdate.clear();
	objectsPreviousUpdate.clear();
	
	// Coordinates of the current chunk the player is on
	int currentChunkX = static_cast<int>(std::floorf(player.position.x / Config::CHUNK_SIZE));
	int currentChunkY = static_cast<int>(std::floorf(player.position.z / Config::CHUNK_SIZE));
	

	// Iterate through player's surrounding chunks
	for (int offsetY = -visibleChunks; offsetY <= visibleChunks; offsetY++)
		for (int offsetX = -visibleChunks; offsetX <= visibleChunks; offsetX++)
		{
			// Chunk currently being viewed
			glm::vec2 viewedChunkCoord = { currentChunkX + offsetX, currentChunkY + offsetY };

			// Check if the chunk exists in the map or not
			if (!chunkMap.contains(viewedChunkCoord))
			{
				if (!oneChunkPerFrame) continue;
				// Insert an instance of the terrain class alongside the chunk coordinate to the chunk map
				chunkMap.insert(std::make_pair(viewedChunkCoord, std::make_shared<Terrain>(viewedChunkCoord, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen, modelMap)));
				oneChunkPerFrame = false;
			}
			
			auto& viewedChunk = chunkMap[viewedChunkCoord];
			viewedChunk->updateDynamics(deltaTime, player);
			chunksPreviousUpdate.push_back(viewedChunk);
			objectsPreviousUpdate.insert(std::end(objectsPreviousUpdate), 
										 std::begin(viewedChunk->getObjects()), 
										 std::end(viewedChunk->getObjects()));
		}

	currentChunk = chunkMap[glm::vec2{currentChunkX, currentChunkY}];

	Statistics::get().addText("Total chunks: " + std::to_string(chunkMap.size()) + "\tLoaded chunks: " + std::to_string(chunksPreviousUpdate.size()));
}

std::shared_ptr<Terrain> World::getCurrentChunk() const
{
	return currentChunk;
}

std::shared_ptr<Terrain> World::getChunk(const Entity& entity) const
{
	// Relative chunk coordinate
	int currentChunkX = static_cast<int>(std::floorf(entity.position.x / Config::CHUNK_SIZE));
	int currentChunkY = static_cast<int>(std::floorf(entity.position.z / Config::CHUNK_SIZE));
	glm::vec2 currentChunkCoord = { currentChunkX, currentChunkY };
	
	if (!chunkMap.contains(currentChunkCoord))
		return nullptr;
	else
		return chunkMap.at(currentChunkCoord);
}



std::vector<std::shared_ptr<Terrain>>& World::getLoadedChunks()
{
	return chunksPreviousUpdate;
}

std::vector<std::shared_ptr<Object>>& World::getLoadedObjects()
{
	return objectsPreviousUpdate;
}
