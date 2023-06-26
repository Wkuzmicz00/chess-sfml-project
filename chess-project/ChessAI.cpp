#include "ChessAI.h"

#include <cstdlib>
#include <ctime>


ChessAI::ChessAI()
{
	this->take = false;
	
}
void ChessAI::initPieces(const std::map<std::string, std::vector<std::shared_ptr<Piece>>> piecesAI)
{
	pieces.clear();
	for (auto pieces : piecesAI)
	{
		for (auto piece : pieces.second)
		{
			this->pieces.push_back(piece);
		}
	}

}

std::shared_ptr<Piece> ChessAI::getPiece()
{
	srand(time(NULL));

	int random = (rand() % pieces.size() + 1) - 1;

	std::shared_ptr<Piece> piece = pieces[random];

	pieces.erase(pieces.begin() + random);

	return piece;
}

std::shared_ptr<Square> ChessAI::getMove(const std::vector<std::shared_ptr<Square>> possibleMoves, const std::vector<std::shared_ptr<Square>> possibleTakes)
{
	srand(time(NULL));
	int random1 = (rand() % 2 + 1) - 1;
	int random2 = 0;

	if (possibleTakes.size() > 0)
	{
		if (possibleMoves.size() > 0)
		{
			if (random1 == 0)
			{
				random2 = (rand() % possibleMoves.size() + 1) - 1;
				take = false;
				return possibleMoves[random2];
			}
			else
			{
				random2 = (rand() % possibleTakes.size() + 1) - 1;
				take = true;
				return possibleTakes[random2];
			}
		}
		else
		{
			random2 = (rand() % possibleTakes.size() + 1) - 1;
			take = true;
			return possibleTakes[random2];
		}
	}
	else if (possibleMoves.size() > 0)
	{
		int random2 = (rand() % possibleMoves.size() + 1) - 1;
		take = false;
		return possibleMoves[random2];
	}
}

bool ChessAI::wasTake()
{
	return this->take;
}




