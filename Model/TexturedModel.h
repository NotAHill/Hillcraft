#pragma once
#ifndef TEXTURED_MODEL
#define TEXTURED_MODEL

#include "Model.h"
#include "../Util/Mesh.h"


#include <SFML/Graphics/Image.hpp>

class TexturedModel : public Model
{
public:
	TexturedModel() : ID(0) {}
	TexturedModel(const std::string& mesh, const std::string& texture);
	void addData(const std::vector<float>& vertexPositions, const std::vector<float>& textureCoords, const std::vector<float>& normalDirections, const std::vector<unsigned int>& indices);
	void addData(const Mesh& mesh);
	void bindTexture() const;
	void addTexture(const sf::Image& img);
	const unsigned int& getID() const;
	unsigned int& getID();

private:
	unsigned int ID;
};



#endif // !TEXTURED_MODEL
