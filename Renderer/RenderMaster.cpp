#include "RenderMaster.h"

void RenderMaster::drawQuad(const Vector3& pos)
{
	quadRenderer.add(pos);
}

void RenderMaster::drawTerrain(const Vector3& pos)
{
	terrainRenderer.add(pos);
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	sfmlRenderer.add(drawable);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	terrainRenderer.render(camera);

	quadRenderer.render(camera);

	sfmlRenderer.render(window);

	window.display();
}
