#include "Pawn.h"

#include <iostream>


Pawn::Pawn(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool isWhite)
{
	this->isWhite = isWhite;
	this->currentSquare = currentSquare;

	this->pieceTexture = pieceTexture;
	this->pieceSprite.setTexture(this->pieceTexture);
	this->pieceSprite.setPosition(this->currentSquare->getPos());
}

std::vector<std::shared_ptr<Square>> Pawn::PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleMoves;

	if (Taked)
		return possibleMoves;

	int x = (this->currentSquare->getPos().x/SQUARE_SIZE) -1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) -1;


	if (this->isWhite) 
	{
		if (y - 1 >= 0) 
		{
			if (squares[x][y - 1]->getSquareStatus() == 2)
			{
				possibleMoves.push_back(squares[x][y - 1]);
				if (!this->isMoved)
				{
					if (squares[x][y - 2]->getSquareStatus() == 2)
					{

						possibleMoves.push_back(squares[x][y - 2]);
					}
				}
			}
		}

	}
	else if(!this->isWhite)
	{
		if (y + 1 <= 7)
		{
			if (squares[x][y + 1]->getSquareStatus() == 2)
			{
				possibleMoves.push_back(squares[x][y + 1]);
				if (!this->isMoved)
				{
					if (squares[x][y + 2]->getSquareStatus() == 2)
					{
						possibleMoves.push_back(squares[x][y + 2]);
					}
				}
			}
		}

	}

	return possibleMoves;
}

std::vector<std::shared_ptr<Square>> Pawn::PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>>possibleTakes;

	if (Taked)
		return possibleTakes;


	int x = (this->currentSquare->getPos().x / SQUARE_SIZE) - 1;
	int y = (this->currentSquare->getPos().y / SQUARE_SIZE) - 1;


	if (this->isWhite && y-1 >= 0)
	{
		if (x - 1 >= 0 && squares[x - 1][y - 1]->getSquareStatus() == 0)
		{
			possibleTakes.push_back(squares[x - 1][y - 1]);
		}
		if (x+1 <= 7 && squares[x + 1][y - 1]->getSquareStatus() == 0)
		{
			possibleTakes.push_back(squares[x + 1][y - 1]);
		}
	}
	else if (!this->isWhite && y+1 <= 7)
	{
		if (x-1 >= 0 && squares[x - 1][y + 1]->getSquareStatus() == 1)
		{
			possibleTakes.push_back(squares[x - 1][y + 1]);
		}
		if (x+1 <= 7 && squares[x + 1][y + 1]->getSquareStatus() == 1)
		{
			possibleTakes.push_back(squares[x + 1][y + 1]);
		}
	}

	return possibleTakes;
}

