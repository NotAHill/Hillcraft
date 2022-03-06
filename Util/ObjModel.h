#pragma once
#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "../Maths/glm.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class ObjModel
{
public:
	bool loadFromFile(const std::string& filename)
	{
		try
		{
			std::ifstream inputFile(filename);
			if (!inputFile) return false;

			std::vector<float> positions;
			std::vector<float> colours;
			std::vector<float> normals;
			std::vector<unsigned int> indices;

			for (std::string line; std::getline(inputFile, line);)
			{
				//std::string currentLine = line.substr();
				//if (line.())
			}

			//auto content = getFileContents(filename);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			return false;
		}
	}

private:

};

#endif // !OBJMODEL_H

