#include "World.h"

World::World() :
	heightGen(20.2f, 4, 0.5f, 2.0f, 1),
	colourGen(20.4f, 4, 0.5f, 2.0f),
	chunkMap(),
	chunksPreviousUpdate()
{
	// Maximum possible chunks seen in any direction
	visibleChunks = static_cast<int>(Config::VIEW_DISTANCE / Config::CHUNK_SIZE);
	chunkMap.insert(std::make_pair(glm::vec2{ 0,0 }, std::make_shared<Terrain>(glm::vec2{ 0,0 }, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, &heightGen)));
}

void World::updateChunks(const Camera& camera)
{
	// Reset the previous frame's chunks
	for (auto& chunk : chunksPreviousUpdate)
		chunk->setVisible(false);
	chunksPreviousUpdate.clear();

	// TODO: Calculate relative position

	// Coordinates of the current chunk the player is on
	int currentChunkX = static_cast<int>(camera.getPosition().x / Config::CHUNK_SIZE);
	int currentChunkY = static_cast<int>(camera.getPosition().z / Config::CHUNK_SIZE);

	//currentChunk = chunkMap[{currentChunkX, currentChunkY}];

	// Iterate through player's surrounding chunks
	for (int offsetY = -visibleChunks; offsetY <= visibleChunks; offsetY++)
		for (int offsetX = -visibleChunks; offsetX <= visibleChunks; offsetX++)
		{
			// Chunk currently being viewed
			glm::vec2 viewedChunkCoord = { currentChunkX + offsetX, currentChunkY + offsetY };

			// Check if the chunk exists in the map or not
			if (chunkMap.contains(viewedChunkCoord))
			{
				// Update chunk for current frame
				//chunkMap[viewedChunkCoord]->updateChunk();
				chunkMap[viewedChunkCoord]->setVisible(true);
				// Append chunks to previous frame's chunks
				if (chunkMap[viewedChunkCoord]->isVisible())
					chunksPreviousUpdate.push_back(chunkMap[viewedChunkCoord]);
			}
			else
			{
				// Insert an instance of the terrain class alongside the chunk coordinate to the chunk map
				chunkMap.insert(std::make_pair(viewedChunkCoord, std::make_shared<Terrain>(viewedChunkCoord, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, &heightGen)));
			}
		}


}

std::shared_ptr<Terrain> World::getCurrentChunk() const
{
	return currentChunk;
}

std::vector<std::shared_ptr<Terrain>>& World::getLoadedChunks()
{
	return chunksPreviousUpdate;
}
