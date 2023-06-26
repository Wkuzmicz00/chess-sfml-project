#include "ChessBoard.h"

bool ChessBoard::checkForBlackCheck()
{
	std::vector<std::shared_ptr<Square>> possibleT;

	for (auto& pieces : blackPieces)
	{
		for (auto& piece : pieces.second)
		{
			possibleT = piece->PossibleTakes(squares);
			for (int i = 0; i < possibleT.size(); i++)
			{
				if (possibleT[i] == findKing(1))
				{
					check = true;
					return true;
				}
			}
		}
	}

	check = false;
	return false;
}

bool ChessBoard::checkForWhiteCheck()
{
	std::vector<std::shared_ptr<Square>> possibleT;



	for (auto& pieces : whitePieces)
	{
		for (auto& piece : pieces.second)
		{
			possibleT = piece->PossibleTakes(squares);
			for (int i = 0; i < possibleT.size(); i++)
			{
				if (possibleT[i] == findKing(0))
				{
					check = true;
					return true;
				}
			}
		}
	}

	check = false;
	return false;
}

void ChessBoard::checkForCheckMate()
{
	std::vector<std::shared_ptr<Square>> posbMoves;
	std::vector<std::shared_ptr<Square>> posbMoves1;

	std::vector<std::shared_ptr<Square>> allBlackMoves;
	std::vector<std::shared_ptr<Square>> allWhiteMoves;

	if (checkForBlackCheck())
	{
		for (auto& pieces : whitePieces)
		{
			for (auto& piece : pieces.second)
			{
				posbMoves1 = piece->PossibleMoves(squares);
				SimulateMove(posbMoves1, piece);
				for (int i = 0; i < posbMoves1.size(); i++)
				{
					allWhiteMoves.push_back(posbMoves1[i]);
				}

				posbMoves1 = piece->PossibleTakes(squares);
				SimulateMove(posbMoves1, piece);
				for (int i = 0; i < posbMoves1.size(); i++)
				{
					allWhiteMoves.push_back(posbMoves1[i]);
				}
			}
		}
		if (allWhiteMoves.size() == 0)
		{
			checkMate = true;
		}
	}

	if (checkForWhiteCheck())
	{
		for (auto& pieces : blackPieces)
		{
			for (auto& piece : pieces.second)
			{
				posbMoves = piece->PossibleMoves(squares);
				SimulateMove(posbMoves, piece);
				for (int i = 0; i < posbMoves.size(); i++)
				{
					allBlackMoves.push_back(posbMoves[i]);
				}

				posbMoves = piece->PossibleTakes(squares);
				SimulateMove(posbMoves, piece);
				for (int i = 0; i < posbMoves.size(); i++)
				{
					allBlackMoves.push_back(posbMoves[i]);
				}
			}
		}
		if (allBlackMoves.size() == 0)
		{
			checkMate = true;
		}

	}

	
}
void ChessBoard::checkForStaleMate()
{
	std::vector<std::shared_ptr<Square>> posbMoves;
	std::vector<std::shared_ptr<Square>> posbMoves1;

	std::vector<std::shared_ptr<Square>> allBlackMoves;
	std::vector<std::shared_ptr<Square>> allWhiteMoves;

	for (auto& pieces : blackPieces)
	{
		for (auto& piece : pieces.second)
		{
			posbMoves = piece->PossibleMoves(squares);
			SimulateMove(posbMoves, piece);
			for (int i = 0; i < posbMoves.size(); i++)
			{
				allBlackMoves.push_back(posbMoves[i]);
			}

			posbMoves = piece->PossibleTakes(squares);
			SimulateMove(posbMoves, piece);
			for (int i = 0; i < posbMoves.size(); i++)
			{
				allBlackMoves.push_back(posbMoves[i]);
			}
		}
	}
	if (allBlackMoves.size() == 0)
	{
		staleMate = true;
	}

	if (checkForWhiteCheck())
	{
		for (auto& pieces : blackPieces)
		{
			for (auto& piece : pieces.second)
			{
				posbMoves = piece->PossibleMoves(squares);
				SimulateMove(posbMoves, piece);
				for (int i = 0; i < posbMoves.size(); i++)
				{
					allBlackMoves.push_back(posbMoves[i]);
				}

				posbMoves = piece->PossibleTakes(squares);
				SimulateMove(posbMoves, piece);
				for (int i = 0; i < posbMoves.size(); i++)
				{
					allBlackMoves.push_back(posbMoves[i]);
				}
			}
		}
		if (allBlackMoves.size() == 0)
		{
			staleMate = true;
		}

	}
}

bool ChessBoard::getCheckMateStatus()
{
	return checkMate;
}

bool ChessBoard::getCheckStatus()
{
	return check;
}

bool ChessBoard::getStaleMateStatus()
{
	return staleMate;
}