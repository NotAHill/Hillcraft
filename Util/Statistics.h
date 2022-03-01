#pragma once
#ifndef STATISTICS_H
#define STATISTICS_H

#include <SFML/Graphics.hpp>

class RenderMaster;

class Statistics : private sf::NonCopyable
{
public:
	static Statistics& get();

	void update(sf::Time deltaTime);
	void render(RenderMaster& renderer);
	void toggle();
	void addText(sf::String string);

private:
	Statistics();

	bool showText;
	sf::Time timer;
	sf::Text displayText;
	sf::String fpsString;
	sf::String otherString;
	unsigned int frameCount;
};


#endif STATISTICS_H

