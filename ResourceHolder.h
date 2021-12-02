#pragma once
#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/System/NonCopyable.hpp>

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
	const bool& exists(const std::string& name) 
	{
		return resources.find(name) != resources.end();
	}
	const Resource& get(const std::string& name) 
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

#endif RESOURCEHOLDER_H

