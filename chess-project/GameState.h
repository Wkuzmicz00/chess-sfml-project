#ifndef GAMESTATE_H	
#define GAMESTATE_H

///
/// Klasa obs³uguj¹ca zdarzenia w stanie gry
/// 

#include "StateManager.h"

#include "State.h"
#include "ChessBoard.h"

#include "Button.h"

class GameState : public State
{
private:
	ChessBoard board;

	StateManager* SM;

	bool endGameDisplayed;

	sf::RectangleShape currentTurnWindow;

	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::shared_ptr<Button>> endGameText;
	
	void initCurrentTurnWindow();
	void initButtons();
	void opponentSelection();
public:
	GameState(StateManager& SM);
	virtual ~GameState();

	void handleButtons(std::shared_ptr<Button> button);

	virtual void handleEvents(sf::Event event, sf::Vector2f currentMousePosition);
	virtual void update();
	virtual void render(sf::RenderTarget* Target);
};

#endif // GAMESTATE_H

