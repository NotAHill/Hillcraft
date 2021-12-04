#include "SFMLRenderer.h"

#include <glad/glad.h>

void SFMLRenderer::add(const sf::Drawable& drawable)
{
	drawables.push_back(&drawable);
}

void SFMLRenderer::render(sf::RenderWindow& window)
{
	if (drawables.empty())
		return;

    glDisable(GL_DEPTH_TEST);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    window.pushGLStates();
    window.resetGLStates();

    for (const auto& draw : drawables)
    {
        window.draw(*draw);
    }

    window.popGLStates();
    drawables.clear();
}
