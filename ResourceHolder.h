#pragma once
#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <memory>
#include <string>

template<typename Resource>
class ResourceHolder : private sf::NonCopyable
{
public:
	ResourceHolder(const std::string& _location) : 
		resources(),
		location(_location) {}
	
	void load(const std::string& filename)
	{
		//std::unique_ptr<Resource> resource = std::unique_ptr<Resource>(new Resource());
		auto resource = std::make_unique<Resource>(Resource());
		if (!resource->loadFromFile(location + filename))
			throw;
		resources.insert(std::make_pair(filename.substr(0, filename.find(".")), std::move(resource)));
	}
	const bool& exists(const std::string& name) 
	{
		return resources.find(name) != resources.end();
	}
	const Resource& get(const std::string& name) 
	{
		if (!exists(name))
			throw;
		return *resources.at(name);
	}

private:
	const std::string location;
	std::unordered_map<std::string, std::unique_ptr<Resource>> resources;
};

#endif RESOURCEHOLDER_H

