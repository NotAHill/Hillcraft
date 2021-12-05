#pragma once
#ifndef RENDERMASTER_H
#define RENDERMASTER_H

#include "QuadRenderer.h"
#include "SFMLRenderer.h"

class Game;

class RenderMaster
{
public:
	void drawQuad(const Vector3& pos);
	void drawSFML(const sf::Drawable& drawable);
	void finishRender(sf::RenderWindow& window, const Camera& camera);

private:
	QuadRenderer quadRenderer;
	SFMLRenderer sfmlRenderer;
};



#endif // !RENDERMASTER_H
