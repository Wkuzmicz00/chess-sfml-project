#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece
{
private:
	bool firstMovePossible;

	sf::RectangleShape promotionWindow;
public:
	Pawn(sf::Texture, std::shared_ptr<Square> currentSquare, bool isWhite);


	std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares);
	std::vector<std::shared_ptr<Square>> PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares);

};

#endif // !PAWN_H
