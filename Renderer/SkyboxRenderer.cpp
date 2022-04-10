#include "SkyboxRenderer.h"
#include "../Config.h"

#include <iostream>
#include <SFML/System/Clock.hpp>

SkyboxRenderer::SkyboxRenderer()
{
	const float SIZE = 500.0f;
	std::vector<float> positions
	{
		// Back
		 SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE, -SIZE, 
		-SIZE,  SIZE, -SIZE,
		 SIZE,  SIZE, -SIZE,

		// Front
		-SIZE, -SIZE, SIZE,
		 SIZE, -SIZE, SIZE,
		 SIZE,  SIZE, SIZE,
		-SIZE,  SIZE, SIZE,

		// Right
		SIZE, -SIZE,  SIZE,
		SIZE, -SIZE, -SIZE,
		SIZE,  SIZE, -SIZE,
		SIZE,  SIZE,  SIZE,

		// Left
		-SIZE, -SIZE, -SIZE,
		-SIZE, -SIZE,  SIZE,
		-SIZE,  SIZE,  SIZE,
		-SIZE,	SIZE, -SIZE,

		// Top
		-SIZE,	SIZE,  SIZE,
		 SIZE,  SIZE,  SIZE,
		 SIZE,	SIZE, -SIZE,
		-SIZE,  SIZE, -SIZE,

		// Bottom
		-SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE, -SIZE,
		 SIZE, -SIZE,  SIZE,
		-SIZE, -SIZE,  SIZE,
	};

	std::vector<unsigned int> indices{ 0,  1,  2,  2,  3,  0,
									   4,  5,  6,  6,  7,  4,
									   8,  9,  10, 10, 11, 8,
									   12, 13, 14, 14, 15, 12,
									   16, 17, 18, 18, 19, 16,
									   20, 21, 22, 22, 23, 20 };

	cubeModel.genVAO();
	cubeModel.addVBO(3, positions);
	cubeModel.addEBO(indices);

	std::vector<std::string> files = { "right", "left", "top", "bottom", "front", "back" };

	// Initialise OpenGL cube map
	glGenTextures(1, &cubeModel.getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeModel.getID());

	// Load texture files
	for (int i = 0; i < 6; i++)
	{
		const auto& image = ResourceManager::get().images.get(files[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	}

	// Set texture files
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyboxRenderer::render(const Camera& camera)
{
	static auto& shader = ResourceManager::get().shaders.get("skybox_shader");
	auto convert = [](const glm::mat4& matrix) { return sf::Glsl::Mat4(glm::value_ptr(matrix)); };
	auto convert2 = [](const glm::vec3& v) { return sf::Glsl::Vec3(v.x, v.y, v.z); };

	static sf::Clock clock;

	glDepthFunc(GL_LEQUAL);
	sf::Shader::bind(&shader);

	// Bind textures and VAO
	cubeModel.bindVAO();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeModel.getID());
	//std::cout << cubeModel.getID() << std::endl;
	// Load matrices
	shader.setUniform("projection", convert(camera.getProjectionMatrix()));
	auto matrix = camera.getViewMatrix();

	matrix = glm::rotate(matrix, 0.01f * clock.getElapsedTime().asSeconds(), { 0, 1, 0 });
	matrix[3][0] = matrix[3][1] = matrix[3][2] = 0.0f;
	shader.setUniform("view", convert(matrix));
	shader.setUniform("skyColour", convert2({ Config::RED, Config::GREEN, Config::BLUE }));
	
	glDrawElements(GL_TRIANGLES, cubeModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	sf::Shader::bind(NULL);
	glDepthFunc(GL_LESS);
}
