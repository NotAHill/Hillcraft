#include "RenderMaster.h"

void RenderMaster::drawQuad(const Vector3& position, const Vector3& rotation)
{
	quadRenderer.add(position, rotation);
}

void RenderMaster::drawTerrain(const Vector3& position, const Vector3& rotation)
{
	terrainRenderer.add(position, rotation);
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	sfmlRenderer.add(drawable);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	terrainRenderer.render(camera);

	quadRenderer.render(camera);

	sfmlRenderer.render(window);

	window.display();
}
