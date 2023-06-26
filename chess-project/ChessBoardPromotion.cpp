 #include "ChessBoard.h"

#include <iostream>

void ChessBoard::openPromotionWindow(sf::Vector2f pos)
{
	Square::Status STATUS[2] = { Square::Status::BLACK, Square::Status::WHITE };

	promotionPieces.clear();

	std::string pieces[8] = { "blackQueen", "blackRook", "blackBishop", "blackKnight", "whiteQueen", "whiteRook", "whiteBishop", "whiteKnight" };

	for (int i = 0; i <= 1; i++)
	{
		Square::Status x = promotedPiece->getSquare()->getSquareStatus();
		if (promotedPiece->getSquare()->getSquareStatus() == STATUS[i])
		{
			promotionWindow.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE * 4));
			promotionWindow.setPosition(pos);
			promotionWindow.setOutlineThickness(2);
			promotionWindow.setOutlineColor(sf::Color::Black);
			promotionWindow.setFillColor(sf::Color::White);

			promotionWindowOverlay.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
			promotionWindowOverlay.setFillColor(PossibleMove);

			for (int j = 0; j < 4; j++)
			{
				promotionPieces.push_back(sf::Sprite());
				auto it = pieceTextures.find(pieces[j + 4 * i]);
				promotionPieces[j].setTexture(it->second);
				promotionPieces[j].setPosition(sf::Vector2f(pos.x, pos.y + (j * SQUARE_SIZE)));
			}
		}
	}

}

void ChessBoard::handlePromotion(sf::Event event, sf::Vector2f currentMousePosition)
{
	if (promotionWindow.getGlobalBounds().contains(currentMousePosition))
	{
		Square::Status STATUS[2] = { Square::Status::BLACK, Square::Status::WHITE };
		// zmienna s³uz¹ca do obs³ugi odpowiedniego koloru, dla którego powinna zostaæ wyœwietlona promocja

		std::string pieces[8] = { "blackQueen", "blackRook", "blackBishop", "blackKnight", "whiteQueen", "whiteRook", "whiteBishop", "whiteKnight" };
		std::string pieces2[4] = { "queen", "rook", "bishop", "knight" };

		int x = promotedPiece->getSquare()->getPos().x / SQUARE_SIZE - 1;
		int y = promotedPiece->getSquare()->getPos().y / SQUARE_SIZE - 1;

		std::map<std::string, std::vector<std::shared_ptr<Piece>>> *whichPieces[2];
		whichPieces[0] = &blackPieces;
		whichPieces[1] = &whitePieces;

		for (int color = 0; color <= 1; color++)
		{
			if (promotedPiece != nullptr)
			{
				if (promotedPiece->getSquare()->getSquareStatus() == STATUS[color])
				{
					for (int i = 0; i < 4; i++)
					{
						if (promotionPieces[i].getGlobalBounds().contains(currentMousePosition))
						{
							promotionWindowOverlay.setPosition(promotionPieces[i].getPosition());
							if (event.type == sf::Event::MouseButtonPressed)
							{
								if (event.mouseButton.button == sf::Mouse::Left)
								{
									auto it = pieceTextures.find(pieces[i + 4 * color]);
									if (pieces2[i] == "queen")
										(*whichPieces[color])[pieces2[i]].push_back(std::make_shared<Queen>(it->second, squares[x][y], color));
									if (pieces2[i] == "rook")
										(*whichPieces[color])[pieces2[i]].push_back(std::make_shared<Rook>(it->second, squares[x][y], color));
									if (pieces2[i] == "bishop")
										(*whichPieces[color])[pieces2[i]].push_back(std::make_shared<Bishop>(it->second, squares[x][y], color));
									if (pieces2[i] == "knight")
										(*whichPieces[color])[pieces2[i]].push_back(std::make_shared<Knight>(it->second, squares[x][y], color));


									promotionHandled = true;

									promotionPieces.clear();
									promotionWindow.setSize(sf::Vector2f(0, 0));
									promotionWindowOverlay.setSize(sf::Vector2f(0, 0));


									deletePiece(promotedPiece);
									promotedPiece = nullptr;

									break;
								}
							}

						}
					}
				}
			}
		}
	}
}

bool ChessBoard::promotionIsPossible()
{
	for (auto& pawns : whitePieces)
	{
		if (pawns.first == "pawn")
		{
			for (auto& pawn : pawns.second)
			{
				int y = pawn->getSquare()->getPos().y;

				if (y == 60)
				{
					promotedPiece = pawn;
					openPromotionWindow(pawn->getSquare()->getPos());
					return true;
				}
			}
		}
	}

	for (auto& pawns : blackPieces)
	{
		if (pawns.first == "pawn")
		{
			for (auto& pawn : pawns.second)
			{
				int y = pawn->getSquare()->getPos().y;

				if (y == 480)
				{
					promotedPiece = pawn;
					if (!AIactive)
					{
						openPromotionWindow(pawn->getSquare()->getPos());
					}
					return true;
				}
			}
		}
	}

	return false;
}

