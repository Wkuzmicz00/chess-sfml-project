#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
class Bishop : public Piece
{
private:
public:
	Bishop(sf::Texture pieceTexture, std::shared_ptr<Square>& currentSquare, bool isWhite);

	virtual std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares);
	virtual std::vector<std::shared_ptr<Square>> PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares);
};

#endif // !BISHOP_H