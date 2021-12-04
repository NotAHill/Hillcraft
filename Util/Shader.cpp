#include "Shader.h"
#include "ShaderLoader.h"

#include <iostream>

Shader::Shader()
{ }

Shader::~Shader()
{
	glDeleteProgram(id);
}

bool Shader::loadFromFile(const std::string& vertexFile, const std::string& fragmentFile)
{
	try
	{
		id = loadFromFile(vertexFile, fragmentFile);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return false;
	}
	
}

void Shader::useProgram()
{
	glUseProgram(id);
}

void Shader::loadInt(unsigned int location, int value)
{
	glUniform1i(location, value);
}

void Shader::loadFloat(unsigned int location, float value)
{
	glUniform1f(location, value);
}

void Shader::loadVector2(unsigned int location, const Vector2& vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void Shader::loadVector3(unsigned int location, const Vector3& vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::loadVector4(unsigned int location, const Vector4& vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::loadMatrix4(unsigned int location, const Matrix4& mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

int Shader::getUniform(const char* name)
{
	return glGetUniformLocation(id, name);
}

unsigned int Shader::getID()
{
	return id;
}
