#ifndef KNIGTH_H
#define KNIGTH_H

#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(sf::Texture pieceTexture, std::shared_ptr<Square> currentSquare, bool IsWhite);

	virtual std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares);
	virtual std::vector<std::shared_ptr<Square>> PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares);
};

#endif // !KNIGTH_H