#include "Game.h"

/// 
/// Klasa Game jest odpowiedzialna za uruchomienie gry, stworzenie okna, obs³ugê zdarzeñ, renderowanie i aktualizacjê stanów.
/// Jest to g³owna klasa projektu.
/// 

Game::Game()
{
    try
    {
        initWindow();
    }
    catch (const std::string exception)
    {
        std::cerr << "error: " << exception << std::endl;
        std::cerr << "press ENTER to exit the program...";
        std::cin.get();
    }
    SM.pushState(std::make_shared<MainMenuState>(SM));
}

Game::~Game() {}

void Game::initWindow()
{
    std::ifstream configWindow("Config/windowSettings.ini");
    if (!configWindow.good())
    {
        std::string exception = "incorrectly opened file: windowSettings.ini";
        throw exception;
    }

    sf::VideoMode window_resolution(0, 0);
    std::string title = "";
    int framerate_limit = 0;

    if (configWindow.is_open())
    {
        configWindow >> window_resolution.width >> window_resolution.height;
        configWindow >> framerate_limit;
    }
    if (window_resolution.height != 800 || window_resolution.width != 800)
    {
        std::string exception = "windowSettings.ini: allowed resolution: 800x800";
        throw exception;
    }
    if((framerate_limit) > 360 || (framerate_limit) < 120)
    { 
        std::string exception = "windowSettings.ini: framerate_limit correct value 120-360";
        throw exception;
    }
    configWindow.close();

    this->window.create(window_resolution, "Chesss", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(framerate_limit);
}

void Game::updateSFMLEvents()
{
    while (this->window.pollEvent(this->sfmlEvent))
    {
        if (this->sfmlEvent.type == sf::Event::Closed)
            this->window.close();

        if (SM.currentState() == nullptr)
            this->window.close();
        else
            SM.currentState()->handleEvents(sfmlEvent, sf::Vector2f(sf::Mouse::getPosition(window)));
    }
}

void Game::render()
{
    this->window.clear();

    if (SM.currentState() == nullptr)
    {
        this->window.close();
    }
	else
        this->SM.currentState()->render(&this->window);

    this->window.display();
}

void Game::update()
{
    if (SM.currentState() != nullptr)
    {
        this->SM.currentState()->update();
    }
}

void Game::run()
{
    while (this->window.isOpen())
    {
        if (SM.currentState() == nullptr)
        {
            this->window.close();
            break;
        }
    
        this->updateSFMLEvents();
        this->render();
        this->update();
    }
}
