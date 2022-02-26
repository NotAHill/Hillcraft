#include "TerrainRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Maths/Matrix.h"

#include <SFML/System/Clock.hpp>

TerrainRenderer::TerrainRenderer() :
	size(100.0f),
	maxHeight(30.0f),
	vertexCount(200),
	light({ 0, 0, 0 }, { 0.3f, -1.0f, 0.5f }, { 1.0f, 1.0f, 1.0f }, { 0.1f, 1.0f, 0.5f })
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
			vertices[vertexPointer * 3 + 1] = vertexHeight;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;

			glm::vec3 vertexColour = getColour(vertexHeight / maxHeight);

			colours[vertexPointer * 3] = vertexColour.x;//(float)(vertexPointer % 3 == 0);
			colours[vertexPointer * 3 + 1] = vertexColour.y;//(float)(vertexPointer % 3 == 1);
			colours[vertexPointer * 3 + 2] = vertexColour.z;//(float)(vertexPointer % 3 == 2);

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
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };

	sf::Shader::bind(&shader);
	terrainModel.bindVAO();

	// Set uniforms for lighting calculation
	shader.setUniform("light.direction", convert2(light.getDirection()));
	shader.setUniform("light.colour", convert2(light.getColour()));
	shader.setUniform("light.bias", convert2(light.getBias()));
	shader.setUniform("cameraPos", convert2(camera.getPosition()));

	// Matrices
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));

	for (auto& terrain : terrainList)
	{
		shader.setUniform("model", convert(makeModelMatrix(terrain)));
		glDrawElements(GL_TRIANGLES, terrainModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	terrainList.clear();
	sf::Shader::bind(NULL);
}

float TerrainRenderer::getHeight(const unsigned int& u, const unsigned int& v, const sf::Image& image, const unsigned int& stepSize)
{
	static const float MAX_PIXEL = powf(256.0f, 4.0f);
	// Check bounds
	if (u < 0 || u >= image.getSize().x || v < 0 || v >= image.getSize().y)
		return 0;

	// Get the value of the red channel of greyscale image
	float height = (float)image.getPixel(u * stepSize, v * stepSize).toInteger();
	// Normalise height value between -1 and 1
	height /= MAX_PIXEL;
	return (2.0f * height - 1.0f) * maxHeight;
}

glm::vec3 TerrainRenderer::getColour(const float& height)
{
	if (height <= -0.1f)
		return {0.0f, 0.0f, 1.0f};

	if (height > -0.1f && height <= -0.05f)
		return { 1.0f, 1.0f, 0.8f };

	if (height >= 0.1f && height < 0.25f)
		return { 0.8f, 0.8f, 0.8f };

	if (height >= 0.25f)
		return { 1.0f, 1.0f, 1.0f };

	return { 0.4f, 1.0f, 0.4f };
}

glm::vec3 TerrainRenderer::calculateNormal(const unsigned int& x, const unsigned int& z, const sf::Image& image, const unsigned int& stepSize)
{
	// Calculate height of adjacent vertices (offset=1)
	float heightL = getHeight(x - 1, z, image, stepSize);
	float heightR = getHeight(x + 1, z, image, stepSize);
	float heightD = getHeight(x, z - 1, image, stepSize);
	float heightU = getHeight(x, z + 1, image, stepSize);

	// Create normal vector, y-component is double the offset
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}


