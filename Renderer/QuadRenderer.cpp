#include "QuadRenderer.h"
#include "../Util/ResourceManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void QuadRenderer::render()
{
	auto& shader = ResourceManager::get().shaders.get("basic_shader");

	//ResourceManager::get().shaders.get("basic_shader").useProgram();
	sf::Shader::bind(&shader);
	quadModel.bindVAO();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// For now rotate the square in space to check whether matrix transforms work
	model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// TODO: fix aspect ratio
	shader.setUniform("model", sf::Glsl::Mat4(glm::value_ptr(model)));
	shader.setUniform("view", sf::Glsl::Mat4(glm::value_ptr(view)));
	shader.setUniform("projection", sf::Glsl::Mat4(glm::value_ptr(projection)));


	for (auto& quad : quads)
	{
		//quadModel.bindVAO();
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	quads.clear();
	//sf::Shader::bind(NULL);
}


