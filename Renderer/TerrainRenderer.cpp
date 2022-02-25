#include "TerrainRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Matrix.h"

#include <SFML/System/Clock.hpp>

TerrainRenderer::TerrainRenderer() :
	size(10.0f),
	maxHeight(3.0f),
	vertexCount(100)
{
	sf::Image image = ResourceManager::get().textures.get("heightmap").copyToImage();
	
	unsigned int stepSize = image.getSize().x / vertexCount;
	unsigned int count = vertexCount * vertexCount;
	//size *= vertexCount;

	std::vector<float> vertices(count * 3);
	std::vector<float> colours(count * 3);
	std::vector<float> normals(count * 3);

	std::vector<unsigned int> indices(6 * (vertexCount - 1) * (vertexCount - 1));

	int vertexPointer = 0;
	for (int i = 0; i < vertexCount; i++) 
	{
		for (int j = 0; j < vertexCount; j++) 
		{
			float vertexHeight = getHeight(j, i, image, stepSize);

			vertices[vertexPointer * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexPointer * 3 + 1] = vertexHeight * maxHeight;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;

			glm::vec3 vertexColour = getColour(vertexHeight);

			colours[vertexPointer * 3] = vertexColour.x;//(float)(rand() % 2 == 0);
			colours[vertexPointer * 3 + 1] = vertexColour.y;//(float)(rand() % 2 == 1);
			colours[vertexPointer * 3 + 2] = vertexColour.z;//(float)(rand() % 2 == 0);

			auto normal = calculateNormal(j, i, image, stepSize);

			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;

			vertexPointer++;
		}
	}

	auto getPos = [&](int x, int z) { return (z * vertexCount) + x; };

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

void TerrainRenderer::add(const Vector3& position, const Vector3& rotation)
{
	terrainList.push_back({ position, rotation });
}

void TerrainRenderer::render(const Camera& camera)
{
	auto& shader = ResourceManager::get().shaders.get("terrain_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	static sf::Clock timer;

	sf::Shader::bind(&shader);
	terrainModel.bindVAO();

	// TODO: fix aspect ratio
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));
	
	shader.setUniform("lightColour", sf::Glsl::Vec3{ 1, 1, 1 });
	shader.setUniform("lightPos", sf::Glsl::Vec3{ 5.0f, -2.0f, 5.0f });
	shader.setUniform("viewPos", sf::Glsl::Vec3(camera.position.x, 
												  camera.position.y, 
												  camera.position.z));

	for (auto& terrain : terrainList)
	{
		//terrainModel.bindVAO();
		shader.setUniform("model", convert(makeModelMatrix(terrain)));
		glDrawElements(GL_TRIANGLES, terrainModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	terrainList.clear();
	sf::Shader::bind(NULL);
}

float TerrainRenderer::getHeight(const unsigned int& u, const unsigned int& v, const sf::Image& image, const unsigned int& stepSize)
{
	// Check bounds
	if (u < 0 || u >= image.getSize().x || v < 0 || v >= image.getSize().y)
		return 0;

	// Get the value of the red channel of greyscale image
	float height = (float)image.getPixel(u * stepSize, v * stepSize).b;
	// Normalise height value
	height /= 255.0f;
	// Height is between -1 and 1
	return 2.0f * height - 1.0f;
}

glm::vec3 TerrainRenderer::getColour(const float& height)
{
	if (height <= -0.1f)
		return {0.0f, 0.0f, 1.0f};

	if (height >= 0.2f)
		return { 0.8f, 0.8f, 0.8f };

	return { 0.0f, 1.0f, 0.0f };
}

glm::vec3 TerrainRenderer::calculateNormal(const unsigned int& x, const unsigned int& z, const sf::Image& image, const unsigned int& stepSize)
{
	float heightL = getHeight(x - 1, z, image, stepSize);
	float heightR = getHeight(x + 1, z, image, stepSize);
	float heightD = getHeight(x, z - 1, image, stepSize);
	float heightU = getHeight(x, z + 1, image, stepSize);
	glm::vec3 normal{ heightL - heightR, 2.0f, heightD - heightU };
	return glm::normalize(normal);
}


