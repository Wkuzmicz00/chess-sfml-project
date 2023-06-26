#include "King.h"

King::King(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool isWhite)
{
	this->isWhite = isWhite;
	this->currentSquare = currentSquare;
	this->pieceTexture = pieceTexture;
	this->pieceSprite.setTexture(this->pieceTexture);
	this->pieceSprite.setPosition(this->currentSquare->getPos());
}



std::vector<std::shared_ptr<Square>> King::PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares)
{
	std::vector<std::shared_ptr<Square>> possibleMoves;

	if (Taked)
		return possibleMoves;

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

		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			if (squares[newX][newY]->getSquareStatus() == 2)
			{
				possibleMoves.push_back(squares[newX][newY]);
			}
		}
	}

	//Roszada
	if (!isMoved) 
	{
		for (int i = 0; i <= 1; i++)
		{
			if (squares[x - 2 + 4 * i][y]->getSquareStatus() == Square::EMPTY && squares[x - 1 + 2 * i][y]->getSquareStatus() == Square::EMPTY)
			{
				//krotka roszada
				if (i == 1)
				{
					possibleMoves.push_back(squares[x - 2 + 4 * i][y]);
				}
				//dluga roszada
				if ( i == 0 && squares[x - 3][y]->getSquareStatus() == Square::EMPTY)
				{
					possibleMoves.push_back(squares[x - 2 + 4 * i][y]);
				}
			}

		}
	}



	return possibleMoves;
}

std::vector<std::shared_ptr<Square>> King::PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares)
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

		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
		{
			if (squares[newX][newY]->getSquareStatus() != 2)
			{
				if (squares[newX][newY]->getSquareStatus() != this->currentSquare->getSquareStatus())
				{
					possibleTakes.push_back(squares[newX][newY]);
				}
			}
		}
	}

	return possibleTakes;
}
