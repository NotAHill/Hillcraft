#include "QuadRenderer.h"
#include "../Util/ResourceManager.h"
#include "../Camera.h"
#include "../Maths/Matrix.h"

QuadRenderer::QuadRenderer()
{
	/*auto& shader = Resources().shaders.get("basic_shader");
	shader.useProgram();
	locationProjectionView = glGetUniformLocation(shader.getID(), "projViewMatrix");
	locationModel = glGetUniformLocation(shader.getID(), "modelMatrix");*/

	quadModel.addData(
		{
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
		},
		{
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
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
	//auto& shader = Resources().shaders.get("basic_shader");
	//shader.useProgram();
	//quadModel.bindVAO();
	//shader.loadMatrix4(locationProjectionView, camera.getProjectionViewMatrix());

	
	//sf::Shader::bind(&shader);
	//quadModel.bindVAO();
	//shader.setUniform("projViewMatrix",
	//	sf::Glsl::Mat4(glm::value_ptr(camera.getProjectionViewMatrix())));

	shader.useProgram();
	quadModel.bindVAO();

	shader.loadProjectionMatrix(camera.getProjectionViewMatrix());

	for (auto& quad : quads)
	{
		//shader.setUniform("modelMatrix", sf::Glsl::Mat4(glm::value_ptr(makeModelMatrix({ quad, {0, 0, 0} }))));
		/*shader.loadMatrix4(locationModel, makeModelMatrix({ quad, {0,0,0} }));*/

		shader.loadModelMatrix(makeModelMatrix({ quad, {0, 0, 0} }));

		std::cout << "drawing quads" << std::endl;
		glDrawElements(GL_TRIANGLES, quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	quads.clear();
	//sf::Shader::bind(NULL);
}


