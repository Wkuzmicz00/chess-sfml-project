#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


#include <stack>
#include <fstream>
#include <vector>
#include <iostream>

class State
{
public:
	virtual void handleEvents(sf::Event event, sf::Vector2f currentMousePosition) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* Target) = 0;
	// klasa abstrakcyjna, ktora jest podstawa dla wszystkich stanow gry
};

#endif // STATE_H

