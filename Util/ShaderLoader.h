#pragma once
#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include "FileLoader.h"

#include <glad/glad.h>
#include <string>
#include <stdexcept>

namespace
{
	unsigned int compileShader(const char* source, GLenum shaderType)
	{
		auto shaderID = glCreateShader(shaderType);

		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);

		int success = 0;
		char infoLog[512];

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
			throw std::runtime_error("Unable to load a shader: " + std::string(infoLog));
		}

		return shaderID;
	}

	unsigned int linkProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID)
	{
		auto id = glCreateProgram();

		glAttachShader(id, vertexShaderID);
		glAttachShader(id, fragmentShaderID);

		glLinkProgram(id);

		return id;
	}
}

inline unsigned int load(const std::string& vertShader, const std::string& fragShader)
{
	auto vertexSource = getFileContents(vertShader);
	auto fragmentSource = getFileContents(fragShader);

	auto vertexShaderID = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
	auto fragmentShaderID = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

	auto shaderID = linkProgram(vertexShaderID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderID;
}

#endif // !SHADERLOADER_H

