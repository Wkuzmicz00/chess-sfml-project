#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece
{
private:
public:
	Rook(sf::Texture, std::shared_ptr<Square> currentSquare, bool color);

	std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares);
	std::vector<std::shared_ptr<Square>>PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares);
};

#endif // ROOK_H