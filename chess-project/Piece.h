#ifndef PIECE_H
#define PIECE_H

#include "Square.h"

class Piece
{
protected:
	bool isWhite;

	std::shared_ptr<Square> currentSquare;
	Square::Status stat;

	bool Taked = false;
	std::shared_ptr<Piece> oldPiece;

	std::vector<std::shared_ptr<Square>> oldSquare;

	bool isMoved = false;

	sf::Texture pieceTexture;
	sf::Sprite pieceSprite;
public:
	void move(std::shared_ptr<Square> newSquare);
	void moveBack();
	void take(std::shared_ptr<Piece> taken);
	void setTakenStatus(bool taken);
	bool isTaken();
	bool isMovedBefore();
	void render(sf::RenderTarget* target);
	std::shared_ptr<Square> getSquare();
	sf::Sprite getBounds();
	
	//przekazujemy aktualna pozycje na szachownicy w celu zweryfikowania 
	//czy ruch jest mozliwy
	virtual std::vector<std::shared_ptr<Square>> PossibleMoves(std::vector<std::vector<std::shared_ptr<Square>>> squares) = 0;
	virtual std::vector<std::shared_ptr<Square>> PossibleTakes(std::vector<std::vector<std::shared_ptr<Square>>> squares) = 0;


};

#endif // !PIECE_H

