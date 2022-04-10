#include "SettingsState.h"

#include "MenuState.h"

#include "../Game.h"

#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../GUI/Label.h"

#include <iomanip>
#include <iostream>

SettingsState::SettingsState(Game& game) :
	BaseState(game)
{

	std::cout << "Currently in SETTINGS state" << std::endl;

	auto window = gamePtr->getWindow().getSize();

	auto str = [&](const float& val, const int& dp)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(dp) << val;
		return stream.str();
	};

	/*for (int i = 0; i < 8; i++)
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
	}*/

	auto title = std::make_shared<Label>(true);
	title->text.setCharacterSize(50u);
	title->setText({ "Settings" });
	title->setPosition(window.x / 2, window.y / 2 - 200.0f);
	container.addComponent(title);

	auto colour = std::make_shared<Label>(true);
	colour->setText({ "Colour:" });
	colour->setPosition(window.x / 2 - 450.0f, 150.0f + (window.y - 150.0f) / 6);
	container.addComponent(colour);

	for (int i = 0; i < 3; ++i)
	{
		auto button = std::make_shared<Button>(ButtonSize::XSMALL);
		button->setPosition((i - 1) * button->getSize().x + window.x / 3, 150.0f + (window.y - 150.0f) / 6);
		switch (i)
		{
		case 0:
			button->setText("R:" + str(Config::RED, 1));
			button->setCallback([=]()
				{
					Config::RED = fmod(Config::RED + 0.1f, 1.1f);
					button->setText("R:" + str(Config::RED, 1));
				}); break;
		case 1:
			button->setText("G:" + str(Config::GREEN, 1));
			button->setCallback([=]()
				{
					Config::GREEN = fmod(Config::GREEN + 0.1f, 1.1f);
					button->setText("G:" + str(Config::GREEN, 1));
				}); break;
		case 2:
			button->setText("B:" + str(Config::BLUE, 1));
			button->setCallback([=]()
				{
					Config::BLUE = fmod(Config::BLUE + 0.1f, 1.1f);
					button->setText("B:" + str(Config::BLUE, 1));
				}); break;
		}
		container.addComponent(button);
	}

	auto fog = std::make_shared<Label>(true);
	fog->setText({ "Fog:" });
	fog->setPosition(window.x / 2 - 450.0f, 150.0f + (window.y - 150.0f) * 2.0f / 6);
	container.addComponent(fog);

	for (int i = 0; i < 2; ++i)
	{
		auto button = std::make_shared<Button>(ButtonSize::SMALL, false);
		button->setPosition((i - 1) * button->getSize().x + window.x / 3, 150.0f + (window.y - 150.0f) * 2 / 6 - button->getSize().y / 2);
		switch (i)
		{
		case 0:
			button->setText("Dens:" + str(Config::FOG_DENSITY, 3));
			button->setCallback([=]()
				{
					Config::FOG_DENSITY = fmod(Config::FOG_DENSITY + 0.005f, 1.005f);
					button->setText("Dens:" + str(Config::FOG_DENSITY, 3));
				}); break;
		case 1:
			button->setText("Grad:" + str(Config::FOG_GRADIENT, 1));
			button->setCallback([=]()
				{
					Config::FOG_GRADIENT = fmod(Config::FOG_GRADIENT + 0.5f, 5.5f);
					button->setText("Grad:" + str(Config::FOG_GRADIENT, 1));
				}); break;
		}
		container.addComponent(button);
	}

	auto noise = std::make_shared<Label>(true);
	noise->setText({ "Noise:",  "(S)cale, (A)mp, (F)req, (O)ct, (H)eight" });
	noise->text.setCharacterSize(20u);
	noise->setPosition(window.x / 2 - 300.0f, 150.0f + (window.y - 150.0f) * 3 / 6);
	container.addComponent(noise);

	auto seedLabel = std::make_shared<Label>(true);
	seedLabel->setText({ "Seed:" });
	seedLabel->setPosition(window.x / 2 - 450.0f, 150.0f + (window.y - 150.0f) * 4 / 6);
	container.addComponent(seedLabel);

	auto seedbox = std::make_shared<Textbox>(TextboxSize::WIDE);
	seedbox->setPosition(window.x / 3, 150.0f + (window.y - 150.0f) * 4 / 6);
	seedbox->setCallback([=](const std::string& text)
		{
			try
			{
				auto a = std::stoi(text);
				Config::SEED = a;
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				auto error = std::make_shared<Label>(true, 3.0f);
				error->rect.setFillColor(sf::Color::Red);
				error->text.setCharacterSize(50u);
				error->setText({ "Error: Invalid Input" });
				error->setPosition(window.x / 2.0f, window.y / 2.0f);
				container.addComponent(error);
			}
		});
	container.addComponent(seedbox);

	for (int i = 0; i < 5; ++i)
	{
		auto button = std::make_shared<Button>(ButtonSize::XSMALL, false);
		button->setPosition((i - 3) * button->getSize().x + window.x / 3 - 30.0f, 150.0f + (window.y - 150.0f) * 5 / 6 - button->getSize().y / 2);
		switch (i)
		{
		case 0:
			button->setText("S:" + str(Config::SCALE, 0));
			button->setCallback([=]()
				{
					Config::SCALE = fmod(Config::SCALE + 5.0f, 50.0f);
					button->setText("S:" + str(Config::SCALE, 0));
				}); break;
		case 1:
			button->setText("A:" + str(Config::PERSISTANCE, 2));
			button->setCallback([=]()
				{
					Config::PERSISTANCE = fmod(Config::PERSISTANCE + 0.05f, 1.05f);
					button->setText("A:" + str(Config::PERSISTANCE, 2));
				}); break;
		case 2:
			button->setText("F:" + str(Config::LACUNARITY, 1));
			button->setCallback([=]()
				{
					Config::LACUNARITY = fmod(Config::LACUNARITY + 0.1f, 2.1f) + 1.0f;
					button->setText("F:" + str(Config::LACUNARITY, 1));
				}); break;
		case 3:
			button->setText("O:" + std::to_string(Config::OCTAVES));
			button->setCallback([=]()
				{
					Config::OCTAVES = (Config::OCTAVES % 8) + 1;
					button->setText("O:" + std::to_string(Config::OCTAVES));
				}); break;
		case 4:
			button->setText("H:" + str(Config::MAX_HEIGHT, 0));
			button->setCallback([=]()
				{
					Config::MAX_HEIGHT = fmod(Config::MAX_HEIGHT + 5.0f, 55.0f);
					button->setText("H:" + str(Config::MAX_HEIGHT, 0));
				}); break;
		}
		container.addComponent(button);
	}



	auto backButton = std::make_shared<Button>(ButtonSize::SMALL, false);
	backButton->setText("Back");
	backButton->setPosition({ window.x - 200.0f, window.y - 100.0f });
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