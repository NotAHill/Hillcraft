#include "World.h"
#include "../Util/Statistics.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include "../Entities/Friendly.h"

#include <iostream>
#include <string>

World::World() :
	heightGen(Config::SCALE, Config::OCTAVES, Config::PERSISTANCE, Config::LACUNARITY, (Config::SEED == -1) ? rand() : Config::SEED),
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
	modelMap["enemy"] = std::make_shared<TexturedModel>("sphere", "rock");
	modelMap["shop"] = std::make_shared<TexturedModel>("stall", "shop");

	chunkMap[{0, 0}] = std::make_shared<Terrain>(glm::vec2{ 0,0 }, Config::CHUNK_SIZE, Config::VERTEX_COUNT, Config::MAX_HEIGHT, heightGen, modelMap);
}

void World::updateChunks(const float& deltaTime, Player& player)
{
	static int killCounter = 0;

	bool oneChunkPerFrame = true;

	// Reset the previous frame's chunks (Maybe unnecessary)
	for (auto& chunk : chunksPreviousUpdate)
		chunk->setVisible(false);

	// Clear all the previous frames objects/chunks
	chunksPreviousUpdate.clear();
	objectsPreviousUpdate.clear();
	
	auto getChunkPos = [&](float val)
	{
		return static_cast<int>(std::floorf(val / Config::CHUNK_SIZE));
	};

	// Coordinates of the current chunk the player is on
	int currentChunkX = getChunkPos(player.position.x);
	int currentChunkY = getChunkPos(player.position.z);
	

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
			auto& enemies = viewedChunk->getEnemies();
			for (auto& enemy : enemies)
			{
				enemy->update(deltaTime, player);
				enemy->position.y = viewedChunk->getHeightOfTerrain(enemy->position.x, enemy->position.z) + 2.0f;
				enemy->box.update(enemy->position);
				if (!enemy->isAlive) killCounter++;
				//if ((getChunkPos(enemy->position.x) != currentChunkX || getChunkPos(enemy->position.z) != currentChunkY) && ++counter >= 11)
				//{
				//	if (chunkMap.contains(glm::vec2{ getChunkPos(enemy->position.x), getChunkPos(enemy->position.z) }))
				//		chunkMap[glm::vec2{ getChunkPos(enemy->position.x), getChunkPos(enemy->position.z) }]->getEnemies().push_back(enemy);
				//	//enemies.erase(it--);
				//}
			}
			enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](std::shared_ptr<Enemy> enemy) { return !enemy->isAlive; }), enemies.end());
			//for (auto it = viewedChunk->getEnemies().begin(); it != viewedChunk->getEnemies().end(); it++)
			//{
			//	(*it)->position.y = viewedChunk->getHeightOfTerrain((*it)->position.x, (*it)->position.z) + 2.0f;
			//	(*it)->update(deltaTime, player);

			//	if (getChunkPos((*it)->position.x) != currentChunkX || getChunkPos((*it)->position.z) != currentChunkY)
			//	{
			//		if (chunkMap.contains(glm::vec2{ getChunkPos((*it)->position.x), getChunkPos((*it)->position.z) }))
			//		{
			//			chunkMap[glm::vec2{ getChunkPos((*it)->position.x), getChunkPos((*it)->position.z) }]->getEnemies().push_back(*it);
			//			viewedChunk->getEnemies().erase(it--);
			//		}
			//		
			//	}
			//}

			chunksPreviousUpdate.push_back(viewedChunk);
			objectsPreviousUpdate.insert(std::end(objectsPreviousUpdate), std::begin(viewedChunk->getObjects()), std::end(viewedChunk->getObjects()));
			objectsPreviousUpdate.insert(std::end(objectsPreviousUpdate), std::begin(viewedChunk->getEnemies()), std::end(viewedChunk->getEnemies()));
			objectsPreviousUpdate.insert(std::end(objectsPreviousUpdate), std::begin(viewedChunk->getFriendlies()), std::end(viewedChunk->getFriendlies()));
			
			//chunkMap[viewedChunkCoord]->setVisible(true);
			//if (chunkMap[viewedChunkCoord]->isVisible())
			//	chunksPreviousUpdate.push_back(chunkMap[viewedChunkCoord]);
		}

	currentChunk = chunkMap[glm::vec2{currentChunkX, currentChunkY}];

	Statistics::get().addText("Total chunks: " + std::to_string(chunkMap.size()) + "\tLoaded chunks: " + std::to_string(chunksPreviousUpdate.size()));
	Statistics::get().addText("Kill Count: " + std::to_string(killCounter));
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
