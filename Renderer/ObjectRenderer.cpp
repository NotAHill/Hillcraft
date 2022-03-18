#include "ObjectRenderer.h"
#include "../Maths/Matrix.h"

void ObjectRenderer::addObject(const Object& object)
{
	// Get the batch which contains the textured model
	
	// Add the object to an existing batch otherwise make a new batch
	if (objects.contains(object.getModel()))
	{
		objects[object.getModel()].push_back(object);
	}
	else
	{
		std::vector<Object> newBatch;
		newBatch.push_back(object);
		objects.insert({ object.getModel(), newBatch });
	}
}

void ObjectRenderer::render(const Camera& camera, std::vector<Light*> lights)
{
	static auto& shader = ResourceManager::get().shaders.get("object_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };


	sf::Shader::bind(&shader);

	// Set camera position and matrices
	shader.setUniform("cameraPos", convert2(camera.getPosition()));
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));

	for (const auto& [model, batch]: objects)
	{
		model->bindVAO();
		model->bindTexture();		

		for (const auto& object : batch)
		{
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

			// Get the model matrix and draw elements for each object
			shader.setUniform("model", convert(makeModelMatrix(object)));
			glDrawElements(GL_TRIANGLES, model->getIndicesCount(), GL_UNSIGNED_INT, nullptr);
			//glDrawArrays(GL_TRIANGLES, 0, model->getIndicesCount());
		}
	}

	objects.clear();
	sf::Shader::bind(NULL);
}
