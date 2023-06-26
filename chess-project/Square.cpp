#include "Square.h"

Square::Square(sf::Vector2f position,  sf::Color color)
{
	this->squareStatus = EMPTY;

	this->position = position;
	this->color = color;

	this->square.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
	this->square.setPosition(this->position);
	this->square.setFillColor(this->color);
}

sf::Vector2f Square::getPos()
{
	return this->position;
}

void Square::setSquareStatus(Square::Status status)
{
	this->squareStatus = status;
}

void Square::render(sf::RenderTarget* Target)
{
	Target->draw(this->square);
}

Square::Status Square::getSquareStatus()
{
	return this->squareStatus;
}