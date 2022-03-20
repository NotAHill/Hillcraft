#include "World.h"
#include "Util/Statistics.h"

#include <iostream>

World::World() :
	heightGen(Config::SCALE, Config::OCTAVES, Config::PERSISTANCE, Config::LACUNARITY),
	//colourGen(20.4f, 4, 0.5f, 2.0f),
	chunkMap(),
	chunksPreviousUpdate()
{
	// Maximum possible chunks seen in any direction
	visibleChunks = Config::RENDER_DISTANCE; //static_cast<int>(std::floorf(Config::VIEW_DISTANCE / Config::CHUNK_SIZE));
	chunkMap.insert(std::make_pair(glm::vec2{ 0,0 }, std::make_shared<Terrain>(glm::vec2{ 0,0 }, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen)));
}

void World::updateChunks(const Entity& entity)
{
	bool oneChunkPerFrame = true;

	// Reset the previous frame's chunks
	for (auto& chunk : chunksPreviousUpdate)
		chunk->setVisible(false);
	chunksPreviousUpdate.clear();

	// TODO: Calculate relative position

	// Coordinates of the current chunk the player is on
	int currentChunkX = static_cast<int>(std::floorf(entity.position.x / Config::CHUNK_SIZE));
	int currentChunkY = static_cast<int>(std::floorf(entity.position.z / Config::CHUNK_SIZE));
	//std::cout << currentChunkX << " " << currentChunkY << std::endl;
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
				chunkMap.insert(std::make_pair(viewedChunkCoord, std::make_shared<Terrain>(viewedChunkCoord, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen)));
				oneChunkPerFrame = false;
			}

			chunksPreviousUpdate.push_back(chunkMap[viewedChunkCoord]);
			//chunkMap[viewedChunkCoord]->setVisible(true);
			//if (chunkMap[viewedChunkCoord]->isVisible())
			//	chunksPreviousUpdate.push_back(chunkMap[viewedChunkCoord]);
		}

	currentChunk = chunkMap[glm::vec2{currentChunkX, currentChunkY}];

	Statistics::get().addText("Total chunks: " + std::to_string(chunkMap.size()));
	Statistics::get().addText("Loaded chunks: " + std::to_string(chunksPreviousUpdate.size()));
}

std::shared_ptr<Terrain> World::getCurrentChunk() const
{
	return currentChunk;
}

std::vector<std::shared_ptr<Terrain>>& World::getLoadedChunks()
{
	return chunksPreviousUpdate;
}
