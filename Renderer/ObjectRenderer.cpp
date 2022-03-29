#include "ObjectRenderer.h"
#include "../Maths/Matrix.h"
#include "../Util/ResourceManager.h"

void ObjectRenderer::add(const std::vector<std::shared_ptr<Object>>& _objects)
{
	// Iterate through each object from input
	for (auto& object : _objects)
	{
		add(object);
	}
}

void ObjectRenderer::add(std::shared_ptr<Object> _object)
{
	// Check if there is another object with same model in the hash map
	if (objects.contains(_object->getModel()))
	{
		// Add the object to the existing batch
		objects[_object->getModel()].push_back(*_object);
	}
	else
	{
		// Otherwise make a new batch
		std::vector<Object> newBatch;
		newBatch.push_back(*_object);
		objects.insert({ _object->getModel(), newBatch });
	}
}

void ObjectRenderer::render(const Camera& camera, std::vector<Light*> lights)
{
	// Alias to shader for easier reading/writing
	static auto& shader = ResourceManager::get().shaders.get("object_shader");

	// Convert glm to sf::Glsl for compatibility with sf::Shader
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };


	sf::Shader::bind(&shader);

	// Set the uniforms (projection & skyColour can be in constructor)
	shader.setUniform("cameraPos",	convert2(camera.getPosition()));
	shader.setUniform("view",		convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));
	shader.setUniform("skyColour",	convert2({ Config::RED, Config::GREEN, Config::BLUE }));

	// Iterate through each model in the hash map
	for (const auto& [model, batch]: objects)
	{
		model->bindVAO();
		model->bindTexture();		

		// Iterate through each object in the model batch
		for (const auto& object : batch)
		{
			// Set uniforms for each light
			for (int i = 0; i < Config::MAX_LIGHTS; i++)
			{
				if (i < lights.size())
				{
					shader.setUniform("light[" + std::to_string(i) + "].direction", convert2(lights[i]->getDirection()));
					shader.setUniform("light[" + std::to_string(i) + "].colour",	convert2(lights[i]->getColour()));
					shader.setUniform("light[" + std::to_string(i) + "].bias",		convert2(lights[i]->getBias()));
				}
				else
				{
					// Default remaining lights to 0 so no uniform errors
					shader.setUniform("light[" + std::to_string(i) + "].direction", sf::Glsl::Vec3(0, 0, 0));
					shader.setUniform("light[" + std::to_string(i) + "].colour",	sf::Glsl::Vec3(0, 0, 0));
					shader.setUniform("light[" + std::to_string(i) + "].bias",		sf::Glsl::Vec3(0, 0, 0));
				}
			}

			// Get the model matrix and draw elements for each object
			shader.setUniform("model", convert(makeModelMatrix(object)));
			glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
			//glDrawArrays(GL_TRIANGLES, 0, model->getIndicesCount());
		}
	}

	// Clear the hash map for next frame
	objects.clear();
	sf::Shader::bind(NULL);
}
