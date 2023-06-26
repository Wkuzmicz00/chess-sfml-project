#include "ChessBoard.h"


void ChessBoard::handleFirstClick(sf::Event event, sf::Vector2f currentMousePosition)
{
	if (whiteTurn)
	{
		for (auto& pieces : whitePieces)
		{
			for (auto& piece : pieces.second)
			{
				if (piece->getBounds().getGlobalBounds().contains(currentMousePosition))
				{
					possibleMoves = piece->PossibleMoves(squares);
					possibleTakes = piece->PossibleTakes(squares);

					if (pieces.first == "king")
						checkForCastling = true;

					currentPieceAction = piece;
					SimulateMove(possibleMoves, currentPieceAction);
					SimulateMove(possibleTakes, currentPieceAction);

					showPossibleMovesOverlay(possibleMoves);
					showPossibleTakesOverlay(possibleTakes);

					break;
				}
			}
		}
	}
	if (!whiteTurn && !AIactive)
	{
		for (auto& pieces : blackPieces)
		{
			for (auto& piece : pieces.second)
			{
				if (piece->getBounds().getGlobalBounds().contains(currentMousePosition))
				{
					possibleMoves = piece->PossibleMoves(squares);
					possibleTakes = piece->PossibleTakes(squares);

					if (pieces.first == "king")
						checkForCastling = true;


					currentPieceAction = piece;
					SimulateMove(possibleMoves, currentPieceAction);
					SimulateMove(possibleTakes, currentPieceAction);

					showPossibleMovesOverlay(possibleMoves);
					showPossibleTakesOverlay(possibleTakes);

					break;
				}
			}
		}
	}
}

void ChessBoard::handleSecondClick(sf::Event event, sf::Vector2f currentMousePosition)
{

	for (auto i = 0; i < possibleMoves.size(); i++)
	{
		if (possibleMovesOverlay[i].getGlobalBounds().contains(currentMousePosition))
		{
			moveMade = true;
			currentPieceAction->move(possibleMoves[i]);


			if (castlingPossible) {
				Castling(possibleMoves[i]);
			}

			if (!promotionIsPossible())
			{
				if (whiteTurn)
					whiteTurn = false;
				else
					whiteTurn = true;
				break;
			}

		}
	}
	for (auto i = 0; i < possibleTakes.size(); i++)
	{
		if (possibleTakesOverlay[i].getGlobalBounds().contains(currentMousePosition))
		{
			moveMade = true;
			currentPieceAction->take(findPiece(possibleTakes[i]));
			deletePiece(findPiece(possibleTakes[i]));

			currentPieceAction->move(possibleTakes[i]);


			if (whiteTurn)
				whiteTurn = false;
			else
				whiteTurn = true;
			break;
		}
	}


	checkForCheckMate();
	checkForStaleMate();

	possibleMoves.clear();
	possibleTakes.clear();
	possibleTakesOverlay.clear();
	possibleMovesOverlay.clear();
}

void ChessBoard::handleEvents(sf::Event event, sf::Vector2f currentMousePosition)
{

	if (!promotionIsPossible())
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (firstClick)
				{
					handleFirstClick(event, currentMousePosition);
					firstClick = false;
				}
				else
				{
					handleSecondClick(event, currentMousePosition);
					firstClick = true;
				}
			}
		}
	}
	else
	{
		promotionHandled = false;
		handlePromotion(event, currentMousePosition);
	}
}

void ChessBoard::Castling(std::shared_ptr<Square> move)
{
	if (currentPieceAction == whitePieces["king"][0])
	{
		if (move->getPos().x / 60 - 1 == 6)
		{
			whitePieces["rook"][1]->move(squares[5][7]);
			castlingPossible = false;
		}
		else if (move->getPos().x / 60 - 1 == 2)
		{
			whitePieces["rook"][0]->move(squares[3][7]);
			castlingPossible = false;
		}
	}
	else if (currentPieceAction == blackPieces["king"][0])
	{
		if (move->getPos().x / 60 - 1 == 6)
		{
			blackPieces["rook"][1]->move(squares[5][0]);
			castlingPossible = false;
		}
		else if (move->getPos().x / 60 - 1 == 2)
		{
			blackPieces["rook"][0]->move(squares[3][0]);
			castlingPossible = false;
		}
	}
}

