#include "Terrain.h"
#include "../Util/ResourceManager.h"
#include "../Config.h"
#include "../Maths/Matrix.h"

Terrain::Terrain(const glm::vec2& _offset, const float& _size, const unsigned int& _vertexCount, const float& _maxHeight, FractalNoiseGenerator& _noise) :
	maxHeight(_maxHeight),
	size(_size),
	vertexCount(_vertexCount),
	noise(&_noise),
	offset(_offset),
	visible(false)
{
	position = { offset.x * size, 0, offset.y * size};
	rotation = { 0, 0, 0 };

	generateTerrain();

	//for (int i = 0; i < 10; i++)
	//{
	//	auto x = (float) rand() / (float) RAND_MAX;
	//	auto z = (float) rand() / (float) RAND_MAX;
	//	auto y = getHeightOfTerrain(x * size, z * size);
	//
	//	if (i >= 5)
	//		objects.push_back(Object(rock, { x + position.x, y, z + position.z }, { 0, rand() % 360, 0 }, 1.0f));
	//	else
	//		objects.push_back(Object(tree, { x + position.x, y, z + position.z }, { 0, rand() % 360, 0 }, 0.3f));
	//}
	//std::cout << "Terrain: " << offset.x << ", " << offset.y << " created" << std::endl;
} 

Model& Terrain::getModel()
{
	return terrainModel;
}

float Terrain::getHeightOfTerrain(const float& x, const float& z)
{
	// Position of player in terrain
	float terrainX = x - position.x;
	float terrainZ = z - position.z;

	// Absolute size of grid
	float gridSquareSize = size / (float)(vertexCount - 1);

	// Grid position
	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);

	if (gridX >= vertexCount - 1 || gridZ >= vertexCount - 1 || gridX < 0 || gridZ < 0)
		return -INFINITY;
	
	// Normalised offset in grid
	float xCoord = fmodf(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmodf(terrainZ, gridSquareSize) / gridSquareSize;
	float answer;

	if (xCoord <= (1 - zCoord)) 
	{
		answer = barycentricInterpolation({ 0, heights[gridX][gridZ], 0 }, 
										  { 1, heights[gridX + 1][gridZ], 0}, 
										  { 0, heights[gridX][gridZ + 1], 1}, 
										  {xCoord, zCoord});
	}
	else 
	{
		answer = barycentricInterpolation({ 1, heights[gridX + 1][gridZ], 0 },
										  { 1, heights[gridX + 1][gridZ + 1], 1 }, 
										  { 0, heights[gridX][gridZ + 1], 1}, 
										  {xCoord, zCoord});
	}

	return answer;
}

void Terrain::generateTerrain()
{
	unsigned int count = vertexCount * vertexCount;

	// Allocate memory for vertex data
	std::vector<float> positions(count * 3);
	std::vector<float> colours(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<unsigned int> indices(6 * (vertexCount - 1) * (vertexCount - 1));
	heights.resize(vertexCount, std::vector<float>(vertexCount));

	// Iterate through each vertex
	int vertexPointer = 0;
	for (int z = 0; z < vertexCount; z++)
	{
		for (int x = 0; x < vertexCount; x++)
		{
			// Calculate position values
			float vertexHeight = getHeight(x, z);
			positions[vertexPointer * 3] = (float)x / ((float)vertexCount - 1) * size;
			positions[vertexPointer * 3 + 1] = vertexHeight;
			positions[vertexPointer * 3 + 2] = (float)z / ((float)vertexCount - 1) * size;

			heights[x][z] = vertexHeight;

			// Calculate colour values
			auto vertexColour = getColour(vertexHeight / maxHeight);
			colours[vertexPointer * 3] = vertexColour.x;
			colours[vertexPointer * 3 + 1] = vertexColour.y;
			colours[vertexPointer * 3 + 2] = vertexColour.z;

			// calcualte normals
			auto normal = calculateNormal(x, z);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;

			vertexPointer++;
		}
	}

	// Calculate index values
	int pointer = 0;
	for (int z = 0; z < vertexCount - 1; z++) 
	{
		for (int x = 0; x < vertexCount - 1; x++) 
		{
			int topLeft = (z * vertexCount) + x;
			int topRight = topLeft + 1;
			int bottomLeft = ((z + 1) * vertexCount) + x;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	terrainModel.addData(positions, colours, normals, indices);
}

float Terrain::getHeight(const unsigned int& u, const unsigned int& v)
{
	float height = noise->getNoise((float)u + (float)(vertexCount - 1) * offset.x, (float)v + (float)(vertexCount - 1) * offset.y);
	if (height <= -0.1f)
		height = -0.105f + 0.005f * sinf((float)rand());
	//height = height * height;
	return height * maxHeight;
}

glm::vec3 Terrain::getColour(const float& height)
{
	if (height <= -0.1f) return { 0.65f, 0.95f, 0.95f }; // Ice
	if (height > -0.1f && height <= -0.05f) return { 1.0f, 1.0f, 0.8f }; // Sand
	if (height >= 0.1f && height < 0.25f) return { 0.8f, 0.8f, 0.8f }; // Stone
	if (height >= 0.25f) return { 1.0f, 1.0f, 1.0f }; // Snow
	return { 0.4f, 1.0f, 0.4f }; // Grass
}

glm::vec3 Terrain::calculateNormal(const unsigned int& x, const unsigned int& z)
{
	// Calculate height of adjacent vertices (offset=1)
	float heightL = getHeight(x - 1, z);
	float heightR = getHeight(x + 1, z);
	float heightD = getHeight(x, z - 1);
	float heightU = getHeight(x, z + 1);

	// Create normal vector, y-component is double the offset
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}

void Terrain::setVisible(const bool& _visible)
{
	visible = _visible;
}

const bool& Terrain::isVisible() const
{
	return visible;
}
