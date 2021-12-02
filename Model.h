#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <SFML/System/NonCopyable.hpp>

#include <vector>

class Model : private sf::NonCopyable
{
public:
	Model() {};
	Model(const std::vector<float>& vertexPositions,
		  const std::vector<float>& colourValues,
		  const std::vector<unsigned int>& indices);
	~Model();

	void addData(const std::vector<float>& vertexPositions,
				 const std::vector<float>& colourValues,
				 const std::vector<unsigned int>& indices);

	void deleteData();

	void addVBO(int size, const std::vector<float>& data);
	void bindVAO() const;

	int getIndicesCount() const;

private:
	void addEBO(const std::vector<unsigned int> indices);
	
	int indicesCount = 0;
	unsigned int VAO = 0;
	unsigned int EBO = 0;
	std::vector<unsigned int> VBO_list;
};


#endif // !MODEL_H
