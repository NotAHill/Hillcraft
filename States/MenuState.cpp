#include "MenuState.h"
#include "GameState.h"
#include "../Game.h"
#include "../GUI/Button.h"

MenuState::MenuState(Game& game) :
	BaseState(game)
{
	std::cout << "Currently in MENU state" << std::endl;

	auto playButton = std::make_shared<GUI::Button>();
	playButton->setText("Play Game");
	playButton->setPosition({ gamePtr->getWindow().getSize().x / 2.0f, gamePtr->getWindow().getSize().y / 2.0f });
	playButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
			gamePtr->getStack().pushState<GameState>(*gamePtr);
		});

	auto quitButton = std::make_shared<GUI::Button>();
	quitButton->setText("Quit");
	quitButton->setPosition({ gamePtr->getWindow().getSize().x / 2.0f, gamePtr->getWindow().getSize().y / 2.0f + 75.0f });
	quitButton->setCallback([&]()
		{
			gamePtr->getStack().popState();
		});

	auto testButton = std::make_shared<GUI::Button>();
	testButton->setText("OFF");
	testButton->setToggle(true);
	testButton->setPosition({ 200.0f, 100.0f });
	testButton->setCallback([&]()
		{
			static int counter = 0;
			std::cout << ++counter << std::endl;
		});

	container.addComponent(playButton);
	container.addComponent(quitButton);
	container.addComponent(testButton);
}

bool MenuState::update(sf::Time deltaTime)
{
	return true;
}

void MenuState::render(RenderMaster& renderer)
{
	container.render(renderer);
}

bool MenuState::fixedUpdate(sf::Time deltaTime)
{
	return true;
}

bool MenuState::handleEvent(sf::Event& event)
{
	container.handleEvent(event, gamePtr->getWindow());
	return true;
}
