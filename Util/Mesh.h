#pragma once
#ifndef MESH_H
#define MESH_H

#include "../Maths/glm.h"

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

class Mesh
{
public:
	bool loadFromFile(const std::string& filename)
	{
		try
		{
			// Load the file from the destination
			std::ifstream inputFile(filename);

			// Return false (error) if not found
			if (!inputFile) return false;

			// Holds attributes temporarily
			std::vector<glm::vec3> tempPositions;
			std::vector<glm::vec2> tempTexCoords;
			std::vector<glm::vec3> tempNormals;

			bool doOnce = true;

			// Lambda function which splits string based on delimiter
			auto split = [&](const std::string& s, char delim)
			{
				std::vector<int> result;
				std::stringstream ss(s);
				std::string item;

				while (std::getline(ss, item, delim))
					result.push_back(std::stoi(item));

				return result;
			};

			// Iterate through each line of object file
			for (std::string line; std::getline(inputFile, line);)
			{
				std::stringstream stream;	// Stream used for splitting lines
				std::string junk;			// Holds the identifier text
				stream << line;

				// v = position, vt = texture coords, vn = normal, f = index
				if (line.starts_with("v "))
				{
					glm::vec3 v;
					stream >> junk >> v.x >> v.y >> v.z;
					tempPositions.push_back(v);
				}
				if (line.starts_with("vt "))
				{
					glm::vec2 v;
					stream >> junk >> v.x >> v.y;
					tempTexCoords.push_back(v);
				}
				if (line.starts_with("vn "))
				{
					glm::vec3 v;
					stream >> junk >> v.x >> v.y >> v.z;
					tempNormals.push_back(v);
				}
				if (line.starts_with("f "))
				{
					// Allocate memory for texCoords and normals
					if (doOnce) { texCoords.resize(tempPositions.size() * 2), normals.resize(tempPositions.size() * 3); doOnce = false; }

					// vertices of each triangle
					std::string v1, v2, v3;
					stream >> junk >> v1 >> v2 >> v3;

					// Split into individual vertices
					auto vertex1 = split(v1, '/');
					auto vertex2 = split(v2, '/');
					auto vertex3 = split(v3, '/');

					// Sets the indices, texCoords and normals in correct order
					processVertex(vertex1, tempTexCoords, tempNormals);
					processVertex(vertex2, tempTexCoords, tempNormals);
					processVertex(vertex3, tempTexCoords, tempNormals);
				}
			}

			positions.resize(tempPositions.size() * 3);
			int vertexPointer = 0;
			for (auto& vertex : tempPositions) 
			{
				positions[vertexPointer++] = vertex.x;
				positions[vertexPointer++] = vertex.y;
				positions[vertexPointer++] = vertex.z;
			}

			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			return false;
		}
	}

	// Vertex attributes
	std::vector<float> positions;
	std::vector<unsigned int> indices;
	std::vector<float> texCoords;
	std::vector<float> normals;
private:
	void processVertex(const std::vector<int>& vertices, const std::vector<glm::vec2>& oldTextures, const std::vector<glm::vec3>& oldNormals)
	{
		// Vertices are 1-indexed so subtract 1.
		unsigned int currentVertexPointer = vertices[0] - 1;
		indices.push_back(currentVertexPointer);

		// Textures
		auto& currentTex = oldTextures[vertices[1] - 1];
		texCoords[currentVertexPointer * 2] = currentTex.x;
		texCoords[currentVertexPointer * 2 + 1] = 1 - currentTex.y;

		// Normals
		auto& currentNormal = oldNormals[vertices[2] - 1];
		normals[currentVertexPointer * 3] = currentNormal.x;
		normals[currentVertexPointer * 3 + 1] = currentNormal.y;
		normals[currentVertexPointer * 3 + 2] = currentNormal.z;
	}
};

#endif // !MESH_H



