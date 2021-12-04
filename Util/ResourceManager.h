#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceHolder.h"
#include "Shader.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

class ResourceManager : private sf::NonCopyable
{
public:
	static ResourceManager& get()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}

	ResourceHolder<sf::Font> fonts;
	ResourceHolder<sf::Texture> textures;
	ResourceHolder<Shader> shaders;

private:
	ResourceManager() :
		fonts("res/fonts/"),
		textures("res/textures/"),
		shaders("res/shaders/")
	{
	}
	
};


#endif // !RESOURCEMANAGER_H
