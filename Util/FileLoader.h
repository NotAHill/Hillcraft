#pragma once
#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

inline std::string getFileContents(const std::string& filePath)
{
	std::ifstream inputFile(filePath);

	if (!inputFile.is_open())
		throw std::runtime_error("Unable to open file: " + filePath);

	std::stringstream stream;

	stream << inputFile.rdbuf();
	return stream.str();
}

#endif // !FILELOADER_H
