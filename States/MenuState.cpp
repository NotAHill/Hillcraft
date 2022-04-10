#include "MenuState.h"

#include "GameState.h"
#include "SettingsState.h"

#include "../Game.h"
#include "../GUI/Button.h"
#include "../GUI/Textbox.h"

MenuState::MenuState(Game& game) :
	BaseState(game)
{
	
	std::cout << "Currently in MENU state" << std::endl;

	auto window = gamePtr->getWindow().getSize();


	auto playButton = std::make_shared<Button>();
	playButton->setText("Play Game");
	playButton->setPosition({ window.x / 2.0f, window.y / 2.0f - 100.0f});
	playButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<GameState>(*gamePtr);
		});

	auto settingsButton = std::make_shared<Button>();
	settingsButton->setText("Settings");
	settingsButton->setPosition({ window.x / 2.0f, window.y / 2.0f });
	settingsButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<SettingsState>(*gamePtr);
		});

	auto quitButton = std::make_shared<Button>(ButtonSize::SMALL);
	quitButton->setText("Quit");
	quitButton->setPosition({ window.x / 2.0f, window.y / 2.0f + 100.0f });
	quitButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
		});

	auto testButton = std::make_shared<Button>();
	testButton->setText("OFF");
	testButton->setToggle(true);
	testButton->setPosition({ window.x / 2.0f, window.y / 2.0f + 200.0f });
	testButton->setCallback([=]()
		{
			std::string text = (testButton->active) ? "ON" : "OFF";
			testButton->setText(text);
		});

	auto textbox = std::make_shared<Textbox>(TextboxSize::WIDE);
	textbox->setPosition({ window.x / 2.0f, window.y / 2.0f - 200.0f });
	textbox->setCallback([&](const std::string& text)
		{
			try
			{
				
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		});

	container.addComponent(textbox);
	container.addComponent(playButton);
	container.addComponent(settingsButton);
	container.addComponent(quitButton);
	container.addComponent(testButton);
}

bool MenuState::update(sf::Time deltaTime)
{
	return false;
}

bool MenuState::render(RenderMaster& renderer)
{
	container.render(renderer);

	return false;
}

bool MenuState::fixedUpdate(sf::Time deltaTime)
{
	return false;
}

bool MenuState::handleEvent(sf::Event& event)
{
	container.handleEvent(event, gamePtr->getWindow());
	return false;
}