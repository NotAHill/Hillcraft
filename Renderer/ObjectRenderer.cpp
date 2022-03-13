#include "ObjectRenderer.h"
#include "../Maths/Matrix.h"

void ObjectRenderer::addObject(const Object& object)
{
	std::vector<Object>& batch = objects.at(&object.getModel());
	if (batch.size() != 0)
		batch.push_back(object);
	else
	{
		std::vector<Object> newBatch;
		newBatch.push_back(object);
		objects.insert({ std::move(object.getModel()), newBatch });
	}
}

void ObjectRenderer::render(const Camera& camera, std::vector<Light*> lights)
{
	static auto& shader = ResourceManager::get().shaders.get("terrain_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };


	sf::Shader::bind(&shader);

	// Set camera position and matrices
	shader.setUniform("cameraPos", convert2(camera.getPosition()));
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));

	for (const auto& [model, batch]: objects)
	{
		model.bindVAO();
		model.bindTexture();

		for (const auto& object : batch)
		{
			// Get the model matrix and draw elements for each terrain
			shader.setUniform("model", convert(makeModelMatrix(object)));
			glDrawElements(GL_TRIANGLES, model.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}
