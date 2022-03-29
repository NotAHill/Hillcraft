#pragma once
#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include "../Entities/Camera.h"
#include "../Entities/Object.h"
#include "../World/Light.h"
#include "../Model/TexturedModel.h"

#include <unordered_map>

// Hash function for pointer to TextureModel class
template<>
struct std::hash<TexturedModel*>
{
	std::size_t operator()(TexturedModel* tex) const noexcept
	{
		// Hash based on ID of the model; Each texturedModel has unique ID
		std::size_t h1 = std::hash<unsigned int>{}(tex->getID());
		return h1;
	}
};

class ObjectRenderer
{
public:
	void add(const std::vector<std::shared_ptr<Object>>& _objects);
	void add(std::shared_ptr<Object> _object);
	void render(const Camera& camera, std::vector<Light*> lights);

private:
	std::unordered_map<TexturedModel*, std::vector<Object>> objects;
};
#endif // !OBJECT_RENDERER_H
