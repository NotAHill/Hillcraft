#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceHolder.h"
#include "Shader.h"
#include "../Mesh.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

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
	//ResourceHolder<Shader> shaders;
	ResourceHolder<sf::Shader> shaders;
	ResourceHolder<Mesh> meshes;
	ResourceHolder<sf::Image> images;

private:
	ResourceManager() :
		fonts("res/fonts/"),
		textures("res/textures/"),
		images("res/textures/"),
		shaders("res/shaders/"),
		meshes("res/objects/")
	{
	}
	
};

#endif // !RESOURCEMANAGER_H
