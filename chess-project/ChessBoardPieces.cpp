#include "ChessBoard.h"

std::shared_ptr<Piece> ChessBoard::findPiece(std::shared_ptr<Square> square)
{
	if (square->getSquareStatus() == 1)
	{
		for (auto pieces : whitePieces)
		{
			for (auto piece : pieces.second)
			{
				if (piece->getSquare() == square)
					return piece;
			}
		}
	}

	if (square->getSquareStatus() == 0)
	{
		for (auto pieces : blackPieces)
		{
			for (auto piece : pieces.second)
			{
				if (piece->getSquare() == square)
					return piece;
			}
		}
	}
	return nullptr;
}

void ChessBoard::deletePiece(std::shared_ptr<Piece> piece)
{
	if (piece != nullptr)
	{
		takenPieces.push_back(piece);
		for (auto& pieces : blackPieces)
		{
			for (auto& piec : pieces.second)
			{
				if (piec == piece)
				{
					pieces.second.erase(std::remove(pieces.second.begin(), pieces.second.end(), piec), pieces.second.end());
					break;
				}
			}
		}
		for (auto& pieces : whitePieces)
		{
			for (auto& piec : pieces.second)
			{
				if (piec == piece)
				{
					pieces.second.erase(std::remove(pieces.second.begin(), pieces.second.end(), piec), pieces.second.end());
					break;
				}

			}
		}
	}

}


std::shared_ptr<Square> ChessBoard::findKing(bool color)
{
	if (color == 0)
	{
		for (auto& pieces : blackPieces)
		{
			for (auto& piece : pieces.second)
			{
				if (pieces.first == "king")
					return piece->getSquare();
			}
		}
	}

	if (color == 1)
	{
		for (auto& pieces : whitePieces)
		{
			for (auto& piece : pieces.second)
			{
				if (pieces.first == "king")
					return piece->getSquare();
			}
		}
	}
	return nullptr;
}