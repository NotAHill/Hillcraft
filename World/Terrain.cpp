#include "Terrain.h"
#include "../Util/ResourceManager.h"
#include "../Config.h"


//Terrain::Terrain(const Terrain& terrain)
//{
//}

//Terrain::Terrain(const Terrain& terrain) :
//	maxHeight(terrain.maxHeight),
//	vertexCount(terrain.vertexCount),
//	size(terrain.size)
//{
//	position = terrain.position;
//	rotation = terrain.rotation;
//
//	generateTerrain("heightmap");
//	std::cout << "Wrong terrain Generated" << std::endl;
//}

Terrain::Terrain(const float& _maxHeight, const float& _size, const unsigned int& _vertexCount, glm::vec3 _position, glm::vec3 _rotation) :
	maxHeight(_maxHeight),
	size(_size),
	vertexCount(_vertexCount)
{
	position = _position;
	rotation = _rotation;

	generateTerrain("heightmap");
	std::cout << "Right Terrain generated" << std::endl;
} 

Model& Terrain::getModel()
{
	return terrainModel;
}

void Terrain::generateTerrain(std::string heightmapLocation)
{
	// Convert texture in GPU to image in CPU, allows reading RGB values
	sf::Image image = ResourceManager::get().textures.get(heightmapLocation).copyToImage();

	stepSize = image.getSize().x / vertexCount;
	unsigned int count = vertexCount * vertexCount;

	heights.reserve(count);
	std::vector<float> vertices(count * 3);
	std::vector<float> colours(count * 3);
	std::vector<float> normals(count * 3);

	std::vector<unsigned int> indices(6 * (vertexCount - 1) * (vertexCount - 1));

	auto getPos = [&](int x, int z) { return (z * vertexCount) + x; };

	int vertexPointer = 0;
	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			// Calculate position values
			float vertexHeight = getHeight(j, i, image);
			vertices[vertexPointer * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexPointer * 3 + 1] = vertexHeight;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;

			// Might need to swap
			//heights[getPos(i, j)] = vertexHeight;

			// Calculate colour values
			auto vertexColour = getColour(vertexHeight / maxHeight);
			colours[vertexPointer * 3] = vertexColour.x;
			colours[vertexPointer * 3 + 1] = vertexColour.y;
			colours[vertexPointer * 3 + 2] = vertexColour.z;

			// calcualte normals
			auto normal = calculateNormal(j, i, image);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;

			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz < vertexCount - 1; gz++) {
		for (int gx = 0; gx < vertexCount - 1; gx++) {
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;

			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	terrainModel.addData(vertices, colours, normals, indices);
}

float Terrain::getHeight(const unsigned int& u, const unsigned int& v, const sf::Image& image)
{
	// Check bounds
	if (u < 0 || u >= image.getSize().x || v < 0 || v >= image.getSize().y)
		return 0;

	// Get the integer value of the grayscale image
	float height = (float)image.getPixel(u * stepSize, v * stepSize).toInteger();
	
	// Normalise height value between -1 and 1
	height /= Config::MAX_PIXEL_COLOUR;
	return (2.0f * height - 1.0f) * maxHeight;
}

glm::vec3 Terrain::getColour(const float& height)
{
	if (height <= -0.1f) return { 0.0f, 0.0f, 1.0f }; // Water

	if (height > -0.1f && height <= -0.05f) return { 1.0f, 1.0f, 0.8f }; // Sand

	if (height >= 0.1f && height < 0.25f) return { 0.8f, 0.8f, 0.8f }; // Stone

	if (height >= 0.25f) return { 1.0f, 1.0f, 1.0f }; // Ice

	return { 0.4f, 1.0f, 0.4f }; // Grass
}

glm::vec3 Terrain::calculateNormal(const unsigned int& x, const unsigned int& z, const sf::Image& image)
{
	// Calculate height of adjacent vertices (offset=1)
	float heightL = getHeight(x - 1, z, image);
	float heightR = getHeight(x + 1, z, image);
	float heightD = getHeight(x, z - 1, image);
	float heightU = getHeight(x, z + 1, image);

	// Create normal vector, y-component is double the offset
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}
