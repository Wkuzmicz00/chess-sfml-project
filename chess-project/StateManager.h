#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"
#include <memory>

class StateManager
{
private:
	std::stack<std::shared_ptr<State>> states;
public:
	void pushState(std::shared_ptr<State> state);
	// dodaje nowy stan na stos
	void popState();
	// usuwa aktualny stan i wraca do poprzedniego
	std::shared_ptr<State> currentState();
	// zwraca aktualny stan
};

#endif // !STATEMANAGER_H

