#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include "../Maths/glm.h"
#include <SFML/System/NonCopyable.hpp>
#include <string>


class Shader //: private sf::NonCopyable
{
public:
	Shader();
	~Shader();

	bool loadFromFile(const std::string& vertexFile, const std::string& fragmentFile);

	void useProgram();

	void loadInt(unsigned int location, int value);
	void loadFloat(unsigned int location, float value);
	void loadVector2(unsigned int location, const Vector2& vec);
	void loadVector3(unsigned int location, const Vector3& vec);
	void loadVector4(unsigned int location, const Vector4& vec);
	void loadMatrix4(unsigned int location, const Matrix4& mat);

	int getUniform(const char* name);
	unsigned int getID();

protected:
	//virtual void getUniforms() = 0;
	unsigned int id;
};

#endif // !SHADER_H
