#include "QuadRenderer.h"
#include "../Util/ResourceManager.h"

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
	//ResourceManager::get().shaders.get("basic_shader").useProgram();
	sf::Shader::bind(&ResourceManager::get().shaders.get("basic_shader"));
	quadModel.bindVAO();

	for (auto& quad : quads)
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	quads.clear();
	//sf::Shader::bind(NULL);
}


