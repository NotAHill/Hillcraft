#include "QuadRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Matrix.h"

QuadRenderer::QuadRenderer()
{
	quadModel.addData(
		{
			-0.5, 0,  0.5,
			 0.5, 0,  0.5,
			 0.5, 0, -0.5,
			-0.5, 0, -0.5
		},
		{
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
		},
		{
			0.0, 1.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 1.0, 0.0
		},
		{
			0, 1, 2,
			2, 3, 0
		});
}

void QuadRenderer::add(const Vector3& position, const Vector3& rotation)
{
	quads.push_back({ position, rotation });
}

void QuadRenderer::render(const Camera& camera)
{
	auto& shader = ResourceManager::get().shaders.get("basic_shader");

	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };

	sf::Shader::bind(&shader);
	quadModel.bindVAO();
		
	// TODO: fix aspect ratio
	shader.setUniform("view", convert(camera.getViewMatrix()));
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));


	for (auto& quad : quads)
	{
		//quadModel.bindVAO();
		shader.setUniform("model", convert(makeModelMatrix(quad)));
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	quads.clear();
	sf::Shader::bind(NULL);
}


