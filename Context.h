#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H

#include <glad/glad.h>

#include <SFML/Graphics.hpp>

class Context
{
public:
	Context(sf::VideoMode size, sf::String title, bool fullscreen);

	sf::RenderWindow window;
};

#endif // !CONTEXT_H

