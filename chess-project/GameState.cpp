#include "GameState.h"

GameState::GameState(StateManager& SM)
{
    this->SM = &SM;

    endGameDisplayed = false;

    initCurrentTurnWindow();
    initButtons();
}

GameState::~GameState()
{}

void GameState::handleEvents(sf::Event event, sf::Vector2f currentMousePosition)
{
    board.handleEvents(event, currentMousePosition);
    opponentSelection();

    for (auto button : buttons)
    {
        button->illuminate(currentMousePosition);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (button->isClicked(currentMousePosition))
                {
                    handleButtons(button);
                }
            }
        }
    }

    if (board.getCurrentTurn())
    {
        currentTurnWindow.setFillColor(sf::Color(240, 217, 181));
    }
    else
    {
        currentTurnWindow.setFillColor(sf::Color(181, 136, 99));
    }
}
void GameState::opponentSelection() 
{
    if (board.isMoveMade())
    {
        buttons[2]->setColor(sf::Color::Magenta);
        buttons[3]->setColor(sf::Color::Magenta);
    }
    else
    {
        if (board.isAIactive() == false)
        {
            buttons[2]->setColor(sf::Color::Green);
            buttons[3]->setColor(sf::Color::White);
        }
        else
        {
            buttons[2]->setColor(sf::Color::White);
            buttons[3]->setColor(sf::Color::Green);
        }
    }

}

void GameState::initButtons()
{
    buttons.push_back(std::make_shared<Button>("Restart", sf::Vector2f(600, 200), 25));
    buttons.push_back(std::make_shared<Button>("Wyjdz", sf::Vector2f(700,750), 25));

    buttons.push_back(std::make_shared<Button>("Gracz", sf::Vector2f(600, 300), 25));
    buttons.push_back(std::make_shared<Button>("Bot", sf::Vector2f(600, 350), 25));
}

void GameState::handleButtons(std::shared_ptr<Button> button)
{
    if (button->getText() == "Restart")
	{
		board.restart();
	}
    if(button->getText() == "Wyjdz")
	{
		SM->popState();
	}
    if (button->getText() == "Gracz")
    {
        if (!board.isMoveMade())
        {
            board.setAI(false);
        }
        opponentSelection();
	}
    if (button->getText() == "Bot")
    {
        if (!board.isMoveMade())
        {
            board.setAI(true);
        }
        opponentSelection();
	}
}

void GameState::initCurrentTurnWindow()
{
    currentTurnWindow.setSize(sf::Vector2f(60, 60));
	currentTurnWindow.setFillColor(sf::Color(240, 217, 181));
	currentTurnWindow.setPosition(sf::Vector2f(600, 60));
}

void GameState::update()
{
    if (board.getCheckMateStatus())
    {
        if (board.getCurrentTurn() && !endGameDisplayed)
        {
            endGameText.push_back(std::make_shared<Button>("Wygral Czarny", sf::Vector2f(80, 600), 80));
            endGameDisplayed = true;
		}
        else if(!endGameDisplayed)
        {
            endGameText.push_back(std::make_shared<Button>("Wygral Bialy", sf::Vector2f(80, 600), 80));
            endGameDisplayed = true;
		}
    }
    else if (board.getStaleMateStatus() && !endGameDisplayed)
    {
		endGameText.push_back(std::make_shared<Button>("Remis", sf::Vector2f(80, 600), 80));
		endGameDisplayed = true;
	}

    else
    {
        if (!board.getCurrentTurn() && !board.promotionIsPossible() && board.isAIactive())
            board.AImove();

        endGameText.clear();
        endGameDisplayed = false;
    }

}

void GameState::render(sf::RenderTarget* Target)
{
    board.render(Target);
    Target->draw(currentTurnWindow);

    for (auto text : endGameText)
    {
        text->render(Target);
    }

    for (auto button : buttons)
	{
		button->render(Target);
	}
}
