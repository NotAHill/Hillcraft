#pragma once
#ifndef MESH_H
#define MESH_H

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
			std::vector<float> tempTexCoords;
			std::vector<float> tempNormals;

			// Lambda function which splits string based on delimiter
			auto split = [&](const std::string& s, char delim)
			{
				std::vector<std::string> result;
				std::stringstream ss(s);
				std::string item;

				while (std::getline(ss, item, delim))
					result.push_back(item);

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
					float x, y, z;
					stream >> junk >> x >> y >> z;
					positions.insert(positions.end(), { x, y, z });
				}
				if (line.starts_with("vt "))
				{
					float u, v;
					stream >> junk >> u >> v;
					tempTexCoords.insert(tempTexCoords.end(), { u, v });
				}
				if (line.starts_with("vn "))
				{
					float x, y, z;
					stream >> junk >> x >> y >> z;
					tempNormals.insert(tempNormals.end(), { x, y, z });
				}
				if (line.starts_with("f "))
				{
					// Allocate memory for texCoords and normals
					static bool doOnce = true;
					if (doOnce) { texCoords.resize(tempTexCoords.size()), normals.resize(tempNormals.size()); doOnce = false; }

					// vertices of each triangle
					std::string v1, v2, v3;
					stream >> junk >> v1 >> v2 >> v3;

					// Split into individual vertices
					auto vertex1 = split(v1, '/');
					auto vertex2 = split(v2, '/');
					auto vertex3 = split(v3, '/');

					// Sets the indices, texCoords and normals in correct order
					processVertex(vertex1, indices, tempTexCoords, tempNormals, texCoords, normals);
					processVertex(vertex2, indices, tempTexCoords, tempNormals, texCoords, normals);
					processVertex(vertex3, indices, tempTexCoords, tempNormals, texCoords, normals);
				}
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
	void processVertex(const std::vector<std::string>& vertices, std::vector<unsigned int>& indices,
		const std::vector<float>& oldTextures, const std::vector<float>& oldNormals, std::vector<float>& newTextures,
		std::vector<float>& newNormals)
	{
		// Vertices are 1-indexed so subtract 1.
		int currentVertexPointer = std::stoi(vertices[0]) - 1;
		indices.push_back(currentVertexPointer);

		// Textures
		newTextures[currentVertexPointer * 2] = oldTextures[std::stoi(vertices[1]) - 1];
		newTextures[currentVertexPointer * 2 + 1] = oldTextures[std::stoi(vertices[1])];

		// Normals
		newNormals[currentVertexPointer * 3] = oldNormals[std::stoi(vertices[2]) - 1];
		newNormals[currentVertexPointer * 3 + 1] = oldNormals[std::stoi(vertices[2])];
		newNormals[currentVertexPointer * 3 + 2] = oldNormals[std::stoi(vertices[2]) + 1];
	}
};

#endif // !MESH_H



