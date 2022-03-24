#include "World.h"
#include "../Util/Statistics.h"

#include <iostream>
#include <string>

World::World() :
	heightGen(Config::SCALE, Config::OCTAVES, Config::PERSISTANCE, Config::LACUNARITY, 1),
	//colourGen(20.4f, 4, 0.5f, 2.0f),
	chunkMap(),
	chunksPreviousUpdate(),
	modelMap()
{
	// Maximum possible chunks seen in any direction
	visibleChunks = Config::RENDER_DISTANCE; //static_cast<int>(std::floorf(Config::VIEW_DISTANCE / Config::CHUNK_SIZE));

	// Load models before chunks
	modelMap["rock"] = std::make_shared<TexturedModel>("toonRocks", "rock");
	modelMap["tree"] = std::make_shared<TexturedModel>("tree", "tree");

	chunkMap[{0, 0}] = std::make_shared<Terrain>(glm::vec2{ 0,0 }, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen, modelMap);
}

void World::updateChunks(const Entity& entity)
{
	bool oneChunkPerFrame = true;

	// Reset the previous frame's chunks (Maybe unnecessary)
	for (auto& chunk : chunksPreviousUpdate)
		chunk->setVisible(false);

	// Clear all the previous frames objects/chunks
	chunksPreviousUpdate.clear();
	objectsPreviousUpdate.clear();
	
	// TODO: Calculate relative position

	// Coordinates of the current chunk the player is on
	int currentChunkX = static_cast<int>(std::floorf(entity.position.x / Config::CHUNK_SIZE));
	int currentChunkY = static_cast<int>(std::floorf(entity.position.z / Config::CHUNK_SIZE));
	

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
			
			const auto& viewedChunk = chunkMap[viewedChunkCoord];
			chunksPreviousUpdate.push_back(viewedChunk);
			objectsPreviousUpdate.insert(std::end(objectsPreviousUpdate), std::begin(viewedChunk->getObjects()), std::end(viewedChunk->getObjects()));
			
			//chunkMap[viewedChunkCoord]->setVisible(true);
			//if (chunkMap[viewedChunkCoord]->isVisible())
			//	chunksPreviousUpdate.push_back(chunkMap[viewedChunkCoord]);
		}

	currentChunk = chunkMap[glm::vec2{currentChunkX, currentChunkY}];

	Statistics::get().addText("Total chunks: " + std::to_string(chunkMap.size()) + "\tLoaded chunks: " + std::to_string(chunksPreviousUpdate.size()));
}

std::shared_ptr<Terrain> World::getCurrentChunk() const
{
	return currentChunk;
}



std::vector<std::shared_ptr<Terrain>>& World::getLoadedChunks()
{
	return chunksPreviousUpdate;
}

std::vector<std::shared_ptr<Object>>& World::getLoadedObjects()
{
	return objectsPreviousUpdate;
}
