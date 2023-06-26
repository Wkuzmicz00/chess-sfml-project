#ifndef SQUARE_H
#define SQUARE_H

#include <SFML/Graphics.hpp>

constexpr int SQUARE_SIZE = 60;

class Square
{
public:
	enum Status
	{
		BLACK,
		WHITE,
		EMPTY
	};
private:
	sf::RectangleShape square;
	sf::Vector2f position;
	sf::Color color;

	Square::Status squareStatus;
public:
	Square(sf::Vector2f position, sf::Color color);

	sf::Vector2f getPos();

	void setSquareStatus(Square::Status status);
	Square::Status getSquareStatus();

	void render(sf::RenderTarget* Target);
};

#endif // !SQUARE_H
