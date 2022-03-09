#include "TerrainRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Maths/Matrix.h"
#include "../World/Terrain.h"

#include "../Config.h"

void TerrainRenderer::render(const Camera& camera, std::vector<Light*> lights)
{
	static auto& shader = ResourceManager::get().shaders.get("terrain_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };

	sf::Shader::bind(&shader);

	// Set camera position and matrices
	shader.setUniform("cameraPos", convert2(camera.getPosition()));
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));

	// Iterate through all terrains
	for (auto& terrain : world->getLoadedChunks())
	{
		terrain->getModel().bindVAO();
		
		// Set uniforms for each light
		for (int i = 0; i < Config::MAX_LIGHTS; i++)
		{
			if (i < lights.size())
			{
				shader.setUniform("light[" + std::to_string(i) + "].direction", convert2(lights[i]->getDirection()));
				shader.setUniform("light[" + std::to_string(i) + "].colour", convert2(lights[i]->getColour()));
				shader.setUniform("light[" + std::to_string(i) + "].bias", convert2(lights[i]->getBias()));
			}
			else
			{
				// Default remaining lights to 0 so no uniform errors
				shader.setUniform("light[" + std::to_string(i) + "].direction", sf::Glsl::Vec3(0, 0, 0));
				shader.setUniform("light[" + std::to_string(i) + "].colour", sf::Glsl::Vec3(0, 0, 0));
				shader.setUniform("light[" + std::to_string(i) + "].bias", sf::Glsl::Vec3(0, 0, 0));
			}
		}

		// Get the model matrix and draw elements for each terrain
		shader.setUniform("model", convert(makeModelMatrix(*terrain)));
		glDrawElements(GL_TRIANGLES, terrain->getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	sf::Shader::bind(NULL);
}

void TerrainRenderer::add(World& _world)
{
	world = &_world;
}

