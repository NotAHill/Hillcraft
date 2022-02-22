#include "Statistics.h"
#include "Renderer/RenderMaster.h"
#include "Util/ResourceManager.h"

Statistics::Statistics() :
	text(),
	timer(sf::Time::Zero),
	frameCount(0)
{
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);
	text.setCharacterSize(16u);
}

void Statistics::update(sf::Time deltaTime)
{
	timer += deltaTime;
	frameCount++;

	if (timer >= sf::seconds(1.0f))
	{
		text.setString("FPS " + std::to_string(frameCount) + "\n" +
					   "TPF " + std::to_string(timer.asMicroseconds() / frameCount) + "us");
		timer -= sf::seconds(1.0f);
		frameCount = 0;
	}
}

void Statistics::render(RenderMaster& renderer)
{
	renderer.drawSFML(text);
}

void Statistics::toggle(bool state)
{
	// TODO
}

void Statistics::initFont()
{
	// Workaround solution
	text.setFont(ResourceManager::get().fonts.get("Fixedsys"));
}
