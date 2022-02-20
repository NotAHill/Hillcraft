#include "QuadRenderer.h"
#include "../Util/ResourceManager.h"

#include "../Matrix.h"

QuadRenderer::QuadRenderer()
{
	quadModel.addData(
		{
			-0.5,  0.5, 0,
			 0.5,  0.5, 0,
			 0.5, -0.5, 0,
			-0.5, -0.5, 0
		},
		{
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
			1.0, 1.0, 1.0,
		},
		{
			0, 1, 2,
			2, 3, 0
		});
}

void QuadRenderer::add(const Vector3& position)
{
	quads.push_back(position);
}

void QuadRenderer::render(const Camera& camera)
{
	auto& shader = ResourceManager::get().shaders.get("basic_shader");

	sf::Shader::bind(&shader);
	quadModel.bindVAO();

	// TODO: fix aspect ratio
	shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(camera.getViewMatrix())));
	shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(camera.getProjectionMatrix())));


	for (auto& quad : quads)
	{
		//quadModel.bindVAO();
		shader.setUniform("model", sf::Glsl::Mat4(glm::value_ptr(makeModelMatrix({ quad, {0, 0, 0} }))));
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	quads.clear();
	sf::Shader::bind(NULL);
}


