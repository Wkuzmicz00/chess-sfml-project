#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece
{
private:
public:
	King(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool isWhite);

	virtual std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares);
	virtual std::vector<std::shared_ptr<Square>> PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares);
};

#endif // !KING_H

