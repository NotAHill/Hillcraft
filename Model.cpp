#include "Model.h"

Model::Model(const std::vector<float>& vertexPositions, const std::vector<float>& colourValues, const std::vector<float>& normalPositions, const std::vector<unsigned int>& indices)
{
	addData(vertexPositions, colourValues, normalPositions, indices);
}

Model::~Model()
{
	deleteData();
}

void Model::addData(const std::vector<float>& vertexPositions, const std::vector<float>& colourValues, const std::vector<float>& normalDirections, const std::vector<unsigned int>& indices)
{
	if (VAO != 0)
		deleteData();

	indicesCount = indices.size();

	// Generate the VAO and bind it
	glGenVertexArrays(1, &VAO);
	bindVAO();

	// Create the VBOs and the EBO
	addVBO(3, vertexPositions);
	addVBO(3, colourValues);
	addVBO(3, normalDirections);
	addEBO(indices);
}

void Model::deleteData()
{
	// Deallocate space held by the objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(VBO_list.size(), VBO_list.data());
	glDeleteBuffers(1, &EBO);

	// Reset the member variables
	VBO_list.clear();
	VAO = EBO = indicesCount = 0;
}

void Model::addVBO(int size, const std::vector<float>& data)
{
	// Create the VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Allocate and store the data in the VBO
	glBufferData(GL_ARRAY_BUFFER, 
				 data.size() * sizeof(float),
				 data.data(),
				 GL_STATIC_DRAW);

	// Tells openGL how the read the data in the vector
	glVertexAttribPointer(VBO_list.size(),
						  size,
						  GL_FLOAT,
						  GL_FALSE,
						  0,
						  (void*) 0);

	// Enables the vertex array held at the location
	glEnableVertexAttribArray(VBO_list.size());

	VBO_list.push_back(VBO);
}

void Model::bindVAO() const
{
	glBindVertexArray(VAO);
}


int Model::getIndicesCount() const
{
	return indicesCount;
}

void Model::addEBO(const std::vector<unsigned int> indices)
{
	// Create EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// Reads the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 indices.size() * sizeof(unsigned int),
				 indices.data(),
				 GL_STATIC_DRAW);
}
