#include "QuadRenderer.h"
#include "../Game.h"

QuadRenderer::QuadRenderer(Game& game) :
	gamePtr(&game)
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
	gamePtr->getShaders().get("basic_shader").useProgram();
	quadModel.bindVAO();

	for (auto& quad : quads)
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	quads.clear();
}


