#pragma once
#ifndef SFMLRENDERER_H
#define SFMLRENDERER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

class SFMLRenderer
{
public:
	void add(const sf::Drawable& drawable);
	void render(sf::RenderWindow& window);

private:
	std::vector<const sf::Drawable*> drawables;
};


#endif // !SFMLRENDERER_H
