#include "Knight.h"

#include <iostream>

Knight::Knight(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool isWhite)
{
	this->isWhite = isWhite;
	this->currentSquare = currentSquare;

	this->pieceTexture = pieceTexture;
	this->pieceSprite.setTexture(this->pieceTexture);
	this->pieceSprite.setPosition(this->currentSquare->getPos());
}


std::vector<std::shared_ptr<Square>> Knight::PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleMoves;

	if (Taked)
		return possibleMoves;

	int x = (this->currentSquare->getPos().x / SQUARE_SIZE) - 1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) - 1;

	int directionx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int directiony[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	int newX = 0;
	int newY = 0;

	for (int i = 0; i < 8; i++)
	{
		newX = x + directionx[i];
		newY = y + directiony[i];
		if (newX <= 7 && newX >= 0 && newY <= 7 && newY >= 0)
		{
			if (squares[newX][newY]->getSquareStatus() == 2)
			{
				possibleMoves.push_back(squares[newX][newY]);
			}
		}
	}

	return possibleMoves;
}
std::vector<std::shared_ptr<Square>> Knight::PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleTakes;

	if (Taked)
		return possibleTakes;

	int x = (this->currentSquare->getPos().x / SQUARE_SIZE) - 1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) - 1;

	int directionx[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int directiony[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	int newX = 0;
	int newY = 0;

	if (isWhite)
	{
		for (int i = 0; i < 8; i++)
		{
			newX = x + directionx[i];
			newY = y + directiony[i];
			if (newX <= 7 && newX >= 0 && newY <= 7 && newY >= 0)
			{
				if (squares[newX][newY]->getSquareStatus() == 0)
				{
					possibleTakes.push_back(squares[newX][newY]);
				}
			}
		}
	}
	else if (!isWhite)
	{
		for (int i = 0; i < 8; i++)
		{
			newX = x + directionx[i];
			newY = y + directiony[i];
			if (newX <= 7 && newX >= 0 && newY <= 7 && newY >= 0)
			{
				if (squares[newX][newY]->getSquareStatus() == 1)
				{
					possibleTakes.push_back(squares[newX][newY]);
				}
			}
		}
	}

	return possibleTakes;
}
