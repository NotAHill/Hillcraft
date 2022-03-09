#pragma once
#ifndef RENDERMASTER_H
#define RENDERMASTER_H

#include "QuadRenderer.h"
#include "SFMLRenderer.h"
#include "TerrainRenderer.h"

#include "../Entities/Camera.h"

class Game;

class RenderMaster
{
public:
	void drawQuad(const Vector3& position, const Vector3& rotation);
	void drawWorld(World& world);
	void drawSFML(const sf::Drawable& drawable);
	void addLight(Light& light);
	void finishRender(sf::RenderWindow& window, const Camera& camera);

private:
	QuadRenderer quadRenderer;
	SFMLRenderer sfmlRenderer;
	TerrainRenderer terrainRenderer;

	std::vector<Light*> lights;
};



#endif // !RENDERMASTER_H
