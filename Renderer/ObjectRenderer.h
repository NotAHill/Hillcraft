#pragma once
#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include "../Entities/Camera.h"
#include "../Entities/Object.h"
#include "../World/Light.h"
#include "../TexturedModel.h"

#include <unordered_map>

template<>
struct std::hash<TexturedModel*>
{
	std::size_t operator()(TexturedModel* tex) const noexcept
	{
		std::size_t h1 = std::hash<unsigned int>{}(tex->getID());
		return h1;
	}
};

class ObjectRenderer
{
public:
	void addObject(const Object& object);
	void render(const Camera& camera, std::vector<Light*> lights);

private:
	std::unordered_map<TexturedModel*, std::vector<Object>> objects;
};
#endif // !OBJECT_RENDERER_H
