#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Shader.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>

template<typename Resource>
class ResourceHolder : private sf::NonCopyable
{
public:
	ResourceHolder(const std::string& _location = "") :
		resources(),
		location(_location) {}

	void load(const std::string& filename, std::string name = "")
	{
		try
		{
			auto resource = std::make_unique<Resource>();
			if (!resource->loadFromFile(location + filename))
				throw std::runtime_error("Error: Filename not found, failed to load " + location + filename);

			if (name == "") name = filename.substr(0, filename.find("."));

			resources.insert(std::make_pair(name, std::move(resource)));
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
		}
	}

	void loadShader(const std::string& filename1, const std::string& filename2, std::string name = "")
	{
		try
		{
			auto resource = std::make_unique<Resource>();
			if (!resource->loadFromFile(location + filename1, location + filename2))
				throw std::runtime_error("Error: Filename not found, failed to load "
					+ location + filename1 + " and/or " + location + filename2);

			if (name == "") name = filename1.substr(0, filename1.find("."));

			resources.insert(std::make_pair(name, std::move(resource)));
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
		}
	}

	const bool exists(const std::string& name)
	{
		return resources.find(name) != resources.end();
	}

	Resource& get(const std::string& name)
	{
		try
		{
			if (!exists(name))
				throw std::runtime_error("Error: No resource found, failed to get " + name);
			return *resources.at(name);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
		}
	}

private:
	const std::string location;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};

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
	//ResourceHolder<sf::Shader> shaders;

private:
	ResourceManager() :
		fonts("res/fonts/"),
		textures("res/textures/"),
		shaders("res/shaders/") 
	{
		fonts.load("Fixedsys.ttf");
		fonts.load("Sansation.ttf");
		textures.load("vector.jpg", "background");
		shaders.loadShader("basic_vertex.glsl", "basic_fragment.glsl", "basic_shader");
	}
};

constexpr auto Resources = &ResourceManager::get;

#endif // !RESOURCEMANAGER_H
