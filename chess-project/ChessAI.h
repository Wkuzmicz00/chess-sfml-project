#ifndef CHESSAI_H
#define CHESSAI_H

#include "Piece.h"

class ChessAI
{
private:
	bool take;

	std::vector<std::shared_ptr<Piece>> pieces;
public:
	ChessAI();

	void initPieces(const std::map<std::string, std::vector<std::shared_ptr<Piece>>> piecesAI);
	std::shared_ptr<Piece> getPiece();
	std::shared_ptr<Square> getMove(const std::vector<std::shared_ptr<Square>> possibleMoves, const std::vector<std::shared_ptr<Square>> possibleTakes);
	bool wasTake();
};

#endif // !CHESSAI_H