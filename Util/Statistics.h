#pragma once
#ifndef STATISTICS_H
#define STATISTICS_H

#include <SFML/Graphics.hpp>

class RenderMaster;

class Statistics
{
public:
	Statistics();

	void update(sf::Time deltaTime);
	void render(RenderMaster& renderer);
	void toggle(bool state);

private:
	sf::Time timer;
	sf::Text text;
	unsigned int frameCount;
};

#endif STATISTICS_H

