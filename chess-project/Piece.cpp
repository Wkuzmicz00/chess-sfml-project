#include "Piece.h"

#include <iostream>

std::shared_ptr<Square> Piece::getSquare()
{
	return this->currentSquare;
}

void Piece::move(std::shared_ptr<Square> newSquare)
{
	stat = newSquare->getSquareStatus();

	if (this->isWhite)
	{
		newSquare->setSquareStatus(Square::WHITE);
	}
	else if (!this->isWhite)
	{
		newSquare->setSquareStatus(Square::BLACK);
	}

	currentSquare->setSquareStatus(Square::EMPTY);
	oldSquare.push_back(currentSquare);

	currentSquare = newSquare;
	this->pieceSprite.setPosition(currentSquare->getPos());

	isMoved = true;

}
void Piece::moveBack()
{
	oldSquare.back()->setSquareStatus(currentSquare->getSquareStatus());

	currentSquare->setSquareStatus(stat);

	currentSquare = oldSquare.back();

	oldSquare.pop_back();

	this->pieceSprite.setPosition(currentSquare->getPos());

	if(oldSquare.size() == 0)
		this->isMoved = false;

	if(oldPiece != nullptr)
		this->oldPiece->setTakenStatus(false);
}

void Piece::take(std::shared_ptr<Piece> taken)
{
	if (taken != nullptr)
	{
		taken->setTakenStatus(true);
		this->oldPiece = taken;
	}
}

void Piece::setTakenStatus(bool taken)
{
	this->Taked = taken;
}

bool Piece::isTaken()
{
	return this->Taked;
}

void Piece::render(sf::RenderTarget* target)
{
	target->draw(this->pieceSprite);
}

sf::Sprite Piece::getBounds()
{
	return this->pieceSprite;
}

bool Piece::isMovedBefore()
{
	return this->isMoved;
}