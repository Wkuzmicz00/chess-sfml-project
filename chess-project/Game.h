#ifndef GAME_H
#define GAME_H

#include "StateManager.h";
#include "MainMenuState.h";

class Game
{
private:
	sf::RenderWindow window;
	// okno 
	sf::Event sfmlEvent;
	// zdarzenia	

	sf::Clock dtClock;
	float dt = 0; //todo
	// deltatime

	StateManager SM;

	//inicjalizacje zmiennych
	void initWindow();
	// inicjalizacja okna
	void updateSFMLEvents();

	void updateDt();
	// aktualizacja zdarzen
public:
	Game();
	virtual ~Game();

	void update();
	// aktualizacja gry
	void render();
	// renderowanie gry

	void run();
	// glowna petla gry	
};

#endif // !GAME_H

