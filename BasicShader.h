#pragma once

#include "Util/Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader(const std::string& vertexFile = "res/shaders/basic_vertex.glsl",
		const std::string& fragmentFile = "res/shaders/basic_fragment.glsl");

	void loadProjectionMatrix(const Matrix4& matrix);
	void loadModelMatrix(const Matrix4& matrix);


private:
	void getUniforms();

	unsigned int locPvMatrix;
	unsigned int locModelMatrix;
};

