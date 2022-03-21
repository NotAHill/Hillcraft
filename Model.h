#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <SFML/System/NonCopyable.hpp>

#include <vector>

class Model : private sf::NonCopyable
{
public:
	Model() : VAO(0), EBO(0), indicesCount(0) {};
	Model(const std::vector<float>& vertexPositions,
		  const std::vector<float>& colourValues,
		  const std::vector<float>& normalDirections,
		  const std::vector<unsigned int>& indices);
	~Model();

	virtual void addData(const std::vector<float>& vertexPositions,
				 const std::vector<float>& colourValues,
				 const std::vector<float>& normalDirections,
				 const std::vector<unsigned int>& indices);

	void deleteData();

	void addEBO(const std::vector<unsigned int> indices);
	void genVAO();
	void addVBO(int size, const std::vector<float>& data);
	void bindVAO() const;

	int getIndicesCount() const;

protected:	
	int indicesCount;

	unsigned int VAO;
	unsigned int EBO;
	std::vector<unsigned int> VBO_list;
};


#endif // !MODEL_H
