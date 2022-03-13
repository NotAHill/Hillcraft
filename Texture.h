#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Util/ResourceManager.h"

#include <string>

class Texture
{
public:
	Texture();
	void load(const std::string& name);
	const unsigned int& getID() const;

private:
	unsigned int ID;
};

#endif // !TEXTURE_H


