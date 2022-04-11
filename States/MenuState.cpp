#include "MenuState.h"

#include "GameState.h"
#include "SettingsState.h"

#include "../Game.h"
#include "../GUI/Button.h"
#include "../GUI/Textbox.h"
#include "../GUI/Label.h"

MenuState::MenuState(Game& game) :
	BaseState(game)
{
	
	std::cout << "Currently in MENU state" << std::endl;

	auto window = gamePtr->getWindow().getSize();

	auto title = std::make_shared<Label>(true);
	title->text.setCharacterSize(50u);
	title->setText({ "Hill Craft" });
	title->setPosition({ window.x / 2.0f, window.y / 2.0f - 150.0f });

	auto playButton = std::make_shared<Button>();
	playButton->setText("Play Game");
	playButton->setPosition({ window.x / 2.0f, window.y / 2.0f - 50.0f});
	playButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<GameState>(*gamePtr);
		});

	auto settingsButton = std::make_shared<Button>();
	settingsButton->setText("Settings");
	settingsButton->setPosition({ window.x / 2.0f, window.y / 2.0f + 50.0f});
	settingsButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<SettingsState>(*gamePtr);
		});

	auto quitButton = std::make_shared<Button>(ButtonSize::SMALL);
	quitButton->setText("Quit");
	quitButton->setPosition({ window.x / 2.0f, window.y / 2.0f + 150.0f });
	quitButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
		});

	static auto testButton = std::make_shared<Button>(ButtonSize::WIDE, true);
	testButton->setText("Not Clicked");
	testButton->setToggle(true);
	testButton->setPosition({ window.x / 2.0f, window.y / 2.0f });
	
	testButton->setCallback([&]()
		{
			if (testButton->active) testButton->setText("Clicked");
			else testButton->setText("Not Clicked");
		});

	auto label = std::make_shared<Label>();
	label->setText({ "Hello", "This is a test" });
	label->setPosition({ window.x / 2.0f + 300.0f, window.y / 2.0f });
	label->rect.setFillColor(sf::Color::Cyan);
	//auto label2 = std::make_shared<Label>(true);
	//label2->setText({ "abc123" });
	//label2->rect.setFillColor(sf::Color::Cyan);
	//label2->setPosition({ window.x / 2.0f - 50.0f, window.y / 2.0f + 100.0f });
	//container.addComponent(label2);

	auto textbox = std::make_shared<Textbox>(TextboxSize::WIDE);
	textbox->setPosition({ window.x / 2.0f, window.y / 2.0f - 150.0f });
	textbox->setCallback([=](const std::string& text)
		{
			try
			{
				label->setText({ text });
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		});

	//container.addComponent(textbox);
	container.addComponent(title);
	container.addComponent(playButton);
	container.addComponent(settingsButton);
	//container.addComponent(testButton);
	container.addComponent(quitButton);
	//container.addComponent(label);
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