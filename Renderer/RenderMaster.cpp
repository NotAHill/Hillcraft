#include "RenderMaster.h"

void RenderMaster::drawQuad(const Vector3& position, const Vector3& rotation)
{
	quadRenderer.add(position, rotation);
}

void RenderMaster::drawTerrain(Terrain& terrain)
{
	terrains.push_back(&terrain);
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	sfmlRenderer.add(drawable);
}

void RenderMaster::addLight(Light& light)
{
	lights.push_back(&light);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	// Purple 0.6f, 0.1f, 1.0f
	glClearColor(0.6f, 0.1f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glProvokingVertex(GL_LAST_VERTEX_CONVENTION);

	// Process entities
	//entityRender.render();

	// Process terrain
	terrainRenderer.render(camera, terrains, lights);

	// Quad Rendering for testing
	quadRenderer.render(camera);

	// Lastly, process SFML
	sfmlRenderer.render(window);

	terrains.clear();
	lights.clear();
	window.display();
}
