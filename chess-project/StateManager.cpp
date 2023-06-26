#include "StateManager.h"


void StateManager::pushState(std::shared_ptr<State> state)
{
    states.push(state);
}

void StateManager::popState()
{

    states.pop();
}

std::shared_ptr<State> StateManager::currentState()
{
    if (!states.empty())
    {
        return states.top();
    }
    return nullptr;
}
