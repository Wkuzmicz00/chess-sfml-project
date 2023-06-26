#include "Queen.h"

#include <iostream>


Queen::Queen(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool isWhite)
{
	this->isWhite = isWhite;
	this->currentSquare = currentSquare;

	this->pieceTexture = pieceTexture;
	this->pieceSprite.setTexture(this->pieceTexture);
	this->pieceSprite.setPosition(this->currentSquare->getPos());
}

std::vector<std::shared_ptr<Square>> Queen::PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleMoves;

	if (Taked)
		return possibleMoves;

	int x = (this->currentSquare->getPos().x / SQUARE_SIZE) - 1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) - 1;

	int directionx[8] = { -1, -1, -1, 1, 1, 1, 0, 0};
	int directiony[8] = { 0, 1, -1, 0, -1, 1, 1 , -1 };
	int newX = 0;
	int newY = 0;

	for (int i = 0; i < 8; i++)
	{
		newX = x + directionx[i];
		newY = y + directiony[i];

		while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			if (squares[newX][newY]->getSquareStatus() == 2)
			{
				possibleMoves.push_back(squares[newX][newY]);
			}
			else
			{
				break;
			}

			newX += directionx[i];
			newY += directiony[i];
		}
	}
	return possibleMoves;

}

std::vector<std::shared_ptr<Square>> Queen::PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleTakes;

	if (Taked)
		return possibleTakes;

	int x = (this->currentSquare->getPos().x / SQUARE_SIZE) - 1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) - 1;

	int directionx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
	int directiony[8] = { 0, 1, -1, 0, -1, 1, 1 , -1 };
	int newX = 0;
	int newY = 0;

	for (int i = 0; i < 8; i++)
	{
		newX = x + directionx[i];
		newY = y + directiony[i];

		while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			if (squares[newX][newY]->getSquareStatus() != 2)
			{
				if (squares[newX][newY]->getSquareStatus() != this->currentSquare->getSquareStatus())
				{
					possibleTakes.push_back(squares[newX][newY]);
				}
				break;
			}
			newX += directionx[i];
			newY += directiony[i];
		}
	}

	return possibleTakes;
}