#include "MainMenuState.h"

MainMenuState::MainMenuState(StateManager& SM)
{
    this->SM = &SM;
    initButtons();
}

MainMenuState::~MainMenuState() {}


void MainMenuState::initButtons()
{

    buttons.push_back(std::make_shared<Button>("Graj", sf::Vector2f(100, 100), 50));
    buttons.push_back(std::make_shared<Button>("Wyjdz", sf::Vector2f(100, 200), 50));

}

void MainMenuState::handleEvents(sf::Event event, sf::Vector2f currentMousePosition)
{

    for(auto button : buttons)
	{
		button->illuminate(currentMousePosition);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if(button->isClicked(currentMousePosition))
                {
                    handleClickedButton(button);
                }

            }
        }
	}
}
void MainMenuState::update()
{
}

void MainMenuState::render(sf::RenderTarget* Target)
{
    for (auto button : buttons)
    {
        button->render(Target);
    }
}

void MainMenuState::handleClickedButton(std::shared_ptr<Button> button)
{
    if(button->getText() == "Graj")
    {
		SM->pushState(std::make_shared<GameState>(*SM));
	}
    if(button->getText() == "Wyjdz")
	{
		SM->popState();
	}
}



