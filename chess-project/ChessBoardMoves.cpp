#include "ChessBoard.h"

void ChessBoard::SimulateMove(std::vector<std::shared_ptr<Square>>& moves, std::shared_ptr<Piece> piece)
{
	///
	/// Metoda sprawdzajaca ruch dla wybranej figury
	/// Ka¿dy pion ma swóje ruchy, metoda sprawdza czy ruch jest mozliwy
	/// Przez niemo¿liwy ruch, mo¿na rozumieæ ruch po którym król danej figury jest szachowany
	/// Sprawdzane s¹ równie¿ ruchy podczas wyst¹pienia szacha
	/// Je¿eli w sytuacji szacha, ruch siê go nie pozbêdzie, jest on niemo¿liwy
	/// 

	std::vector<std::shared_ptr<Square>> NewPossibleMoves;
	std::vector<std::shared_ptr<Square>> CastlingMoves;
	int it = 0;
	//roszada
	if (checkForCastling && !piece->isMovedBefore())
	{
		for (auto& move : moves)
		{
			for (int i = 0; i <= 1; i++)
			{
				int x = piece->getSquare()->getPos().x / 60 - 2 + (4 * i) - 1;
				int y = piece->getSquare()->getPos().y / 60 - 1;
				if (move == squares[x][y])
				{
					if (findPiece(squares[0 + 7 * i][y]) != nullptr)
					{
						if (!findPiece(squares[0 + 7 * i][y])->isMovedBefore() && !piece->isMovedBefore())
						{
							castlingPossible = true;
							CastlingMoves.push_back(move);
						}
					}
					moves.erase(moves.begin() + it);
				}
			}
			it++;
		}
		checkForCastling = false;
	}
	/// Sprawdza czy wystepuje szach po ruchu figury
	if (!checkForBlackCheck() && !checkForWhiteCheck())
	{
		for (auto& move : moves)
		{
			piece->move(move);
			piece->take(findPiece(move));

			if (!checkForBlackCheck() && piece->getSquare()->getSquareStatus() == 1)
			{
				NewPossibleMoves.push_back(move);
			}
			if (!checkForWhiteCheck() && piece->getSquare()->getSquareStatus() == 0)
			{
				NewPossibleMoves.push_back(move);
			}
			piece->moveBack();
		}

		for (auto& move : CastlingMoves)
		{
			piece->move(move);
			piece->take(findPiece(move));

			if (!checkForBlackCheck() && piece->getSquare()->getSquareStatus() == 1)
			{
				NewPossibleMoves.push_back(move);
			}
			if (!checkForWhiteCheck() && piece->getSquare()->getSquareStatus() == 0)
			{
				NewPossibleMoves.push_back(move);
			}
			piece->moveBack();
		}
	}

	/// Obowi¹zkowe zas³oniecie/zbicie w przypadku szacha
	if (checkForWhiteCheck() || checkForBlackCheck())
	{
		for (auto& move : moves)
		{

			piece->take(findPiece(move));
			piece->move(move);

			if (!checkForWhiteCheck() && piece->getSquare()->getSquareStatus() == 0)
			{
				NewPossibleMoves.push_back(move);
			}
			if (!checkForBlackCheck() && piece->getSquare()->getSquareStatus() == 1)
			{
				NewPossibleMoves.push_back(move);
			}
			piece->moveBack();
		}
	}

	moves = NewPossibleMoves;
	NewPossibleMoves.clear();
	CastlingMoves.clear();
	checkForCastling = false;
}

void ChessBoard::showPossibleMovesOverlay(const std::vector<std::shared_ptr<Square>> Moves)
{
	int i = 0;
	for (auto move : Moves)
	{
		possibleMovesOverlay.push_back(sf::RectangleShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)));
		possibleMovesOverlay[i].setPosition(move->getPos());
		possibleMovesOverlay[i].setFillColor(PossibleMove);
		i++;
	}
}
void ChessBoard::showPossibleTakesOverlay(const std::vector<std::shared_ptr<Square>> Moves)
{
	int i = 0;
	for (auto move : Moves)
	{
		possibleTakesOverlay.push_back(sf::RectangleShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)));
		possibleTakesOverlay[i].setPosition(move->getPos());
		possibleTakesOverlay[i].setFillColor(PossibleTake);
		i++;
	}
}