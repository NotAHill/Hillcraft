#include "RenderMaster.h"

void RenderMaster::drawQuad(const Vector3& pos)
{
	quadRenderer.add(pos);
}

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	sfmlRenderer.add(drawable);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.6f, 0.1f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	quadRenderer.render(camera);

	sfmlRenderer.render(window);

	window.display();
}
