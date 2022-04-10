#include "SettingsState.h"

#include "MenuState.h"

#include "../Game.h"
#include "../GUI/Button.h"

#include <iomanip>
#include <iostream>

SettingsState::SettingsState(Game& game) :
	BaseState(game)
{

	std::cout << "Currently in SETTINGS state" << std::endl;

	auto window = gamePtr->getWindow().getSize();

	for (int i = 0; i < 8; i++)
	{
		auto button = std::make_shared<Button>();
		button->setPosition((i / 4 + 1) * window.x / 3, (i % 4 + 1) * window.y / 5);

		auto str = [&](const float& val, const int& dp)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(dp) << val;
			return stream.str();
		};

		switch (i)
		{
		case 0:
			button->setText("Red: " + str(Config::RED, 1));
			button->setCallback([=]() 
				{ 
					Config::RED = fmod(Config::RED + 0.1f, 1.1f); 
					button->setText("Red: " + str(Config::RED, 1)); 
				}); break;
		case 1:
			button->setText("Green: " + str(Config::GREEN, 1));
			button->setCallback([=]()
				{
					Config::GREEN = fmod(Config::GREEN + 0.1f, 1.1f);
					button->setText("Green: " + str(Config::GREEN, 1));
				}); break;
		case 2:
			button->setText("Blue: " + str(Config::BLUE, 1));
			button->setCallback([=]()
				{
					Config::BLUE = fmod(Config::BLUE + 0.1f, 1.1f);
					button->setText("Blue: " + str(Config::BLUE, 1));
				}); break;
		case 3:
			button->setText("Render Distance: " + std::to_string(Config::RENDER_DISTANCE));
			button->setCallback([=]()
				{
					Config::RENDER_DISTANCE = (Config::RENDER_DISTANCE + 1) % 5;
					button->setText("Render Distance: " + std::to_string(Config::RENDER_DISTANCE));
				}); break;
		case 4:  button->setCallback([=]() { std::cout << "Button: " << i << std::endl; }); break;
		case 5:  button->setCallback([=]() { std::cout << "Button: " << i << std::endl; }); break;
		case 6:  button->setCallback([=]() { std::cout << "Button: " << i << std::endl; }); break;
		case 7:  button->setCallback([=]() { std::cout << "Button: " << i << std::endl; }); break;
		}
		
		container.addComponent(button);
	}

	auto backButton = std::make_shared<Button>(ButtonSize::SMALL);
	backButton->setText("Back");
	backButton->setPosition({ window.x / 2.0f, window.y / 2.0f + 200.0f });
	backButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<MenuState>(*gamePtr);
		});

	container.addComponent(backButton);
}

bool SettingsState::update(sf::Time deltaTime)
{
	return false;
}

bool SettingsState::render(RenderMaster& renderer)
{
	container.render(renderer);

	return false;
}

bool SettingsState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool SettingsState::handleEvent(sf::Event& event)
{
	container.handleEvent(event, gamePtr->getWindow());
	return false;
}