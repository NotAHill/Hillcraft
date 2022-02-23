#include "TerrainRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Matrix.h"

TerrainRenderer::TerrainRenderer() :
	size(1.0f),
	vertexCount(100)
{
	int count = vertexCount * vertexCount;
	size *= vertexCount;
	std::vector<float> vertices(count * 3);
	std::vector<float> colours(count * 3);
	std::vector<unsigned int> indices(6 * (vertexCount - 1) * (vertexCount - 1));

	int vertexPointer = 0;
	for (int i = 0; i < vertexCount; i++) 
	{
		for (int j = 0; j < vertexCount; j++) 
		{
			vertices[vertexPointer * 3] = (float)j / ((float)vertexCount - 1) * size;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)vertexCount - 1) * size;

			colours[vertexPointer * 3] = 1.0f;//(float)(i % 3 == 0);
			colours[vertexPointer * 3 + 1] = 1.0f;//(float)(i % 3 == 1);
			colours[vertexPointer * 3 + 2] = 1.0f;//(float)(i % 3 == 2);

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

	terrainModel.addData(vertices, colours, indices);
}

void TerrainRenderer::add(const Vector3& position)
{
	terrainList.push_back(position);
}

void TerrainRenderer::render(const Camera& camera)
{
	auto& shader = ResourceManager::get().shaders.get("basic_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };

	sf::Shader::bind(&shader);
	terrainModel.bindVAO();

	// TODO: fix aspect ratio
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));


	for (auto& terrain : terrainList)
	{
		//terrainModel.bindVAO();
		shader.setUniform("model", convert(makeModelMatrix({ terrain, {0, 0, 0} })));
		glDrawElements(GL_TRIANGLES, terrainModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	terrainList.clear();
	sf::Shader::bind(NULL);
}


