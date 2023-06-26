#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "State.h"
#include "StateManager.h"
#include "GameState.h"

#include "Button.h"

class MainMenuState : public State
{
private:
	StateManager* SM;

	std::vector<std::shared_ptr<Button>> buttons;

	void initButtons();

	void handleClickedButton(std::shared_ptr<Button> button);
public:
	MainMenuState(StateManager &SM);
	virtual ~MainMenuState();

	virtual void handleEvents(sf::Event event, sf::Vector2f currentMousePosition);
	// obsluga zdarzen
	virtual void update();
	// aktualizacja stanu gry
	virtual void render(sf::RenderTarget* Target);
	// renderowanie stanu gry

};

#endif // !MAINMENUSTATE_H


