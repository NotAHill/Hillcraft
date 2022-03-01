#include "Statistics.h"
#include "../Renderer/RenderMaster.h"
#include "ResourceManager.h"

Statistics::Statistics() :
	displayText(),
	timer(sf::Time::Zero),
	frameCount(0),
	showText(true)
{
	displayText.setFont(ResourceManager::get().fonts.get("Fixedsys"));
	displayText.setFillColor(sf::Color::White);
	displayText.setOutlineColor(sf::Color::Black);
	displayText.setOutlineThickness(1.0f);
	displayText.setCharacterSize(26u);
}

Statistics& Statistics::get()
{
	static Statistics statistics;
	return statistics;
}

void Statistics::update(sf::Time deltaTime)
{
	timer += deltaTime;
	frameCount++;

	if (timer >= sf::seconds(1.0f))
	{
		fpsString = "FPS " + std::to_string(frameCount) + "\n" +
							  "TPF " + std::to_string(timer.asMicroseconds() / frameCount) + "us\n";
		timer -= sf::seconds(1.0f);
		frameCount = 0;
	}
}

void Statistics::render(RenderMaster& renderer)
{
	displayText.setString(fpsString + otherString);
	if (showText) renderer.drawSFML(displayText);
	otherString.clear();
}

void Statistics::toggle()
{
	showText = !showText;
}

void Statistics::addText(sf::String string)
{
	otherString += string + "\n";
}