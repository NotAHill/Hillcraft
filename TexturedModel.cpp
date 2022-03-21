#include "TexturedModel.h"

TexturedModel::TexturedModel(const std::string& mesh, const std::string& texture)
{
	addData(ResourceManager::get().meshes.get(mesh));
	addTexture(ResourceManager::get().images.get(texture));
}

void TexturedModel::addData(const std::vector<float>& vertexPositions, const std::vector<float>& textureCoords, const std::vector<float>& normalDirections, const std::vector<unsigned int>& indices)
{
	if (VAO != 0)
		deleteData();

	indicesCount = indices.size();

	// Generate the VAO and bind it
	glGenVertexArrays(1, &VAO);
	bindVAO();

	// Create the VBOs and the EBO
	addVBO(3, vertexPositions);
	addVBO(2, textureCoords);
	addVBO(3, normalDirections);
	addEBO(indices);
}

void TexturedModel::addData(const Mesh& mesh)
{
	addData(mesh.positions, mesh.texCoords, mesh.normals, mesh.indices);
}

void TexturedModel::addTexture(const sf::Image& img)
{	
	// Create texture
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
	
	// Set texture attributes
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
}

const unsigned int& TexturedModel::getID() const
{
	return ID;
}

unsigned int& TexturedModel::getID()
{
	return ID;
}

void TexturedModel::bindTexture() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}