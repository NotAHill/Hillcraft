#include "RenderMaster.h"

void RenderMaster::drawQuad(const Vector3& position, const Vector3& rotation)
{
	quadRenderer.add(position, rotation);
}

void RenderMaster::drawWorld(World& world)
{
	objectRenderer.add(world.getLoadedObjects());
	terrainRenderer.add(world);
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	sfmlRenderer.add(drawable);
}

void RenderMaster::drawObject(const Object& object)
{
	// Defunct
	//objectRenderer.addObject(object);
}

void RenderMaster::addLight(Light& light)
{
	lights.push_back(&light);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	// Purple 0.6f, 0.1f, 1.0f
	glClearColor(Config::RED, Config::GREEN, Config::BLUE, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glProvokingVertex(GL_LAST_VERTEX_CONVENTION);



	// Process world
	terrainRenderer.render(camera, lights);

	// Quad Rendering for testing
	quadRenderer.render(camera);

	// Process entities
	objectRenderer.render(camera, lights);

	// Draw skybox
	skyboxRenderer.render(camera);

	// Lastly, process SFML
	sfmlRenderer.render(window);

	lights.clear();
	window.display();
}
