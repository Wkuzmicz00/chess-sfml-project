#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	squares.resize(8, std::vector<std::shared_ptr<Square>>(8));

	initBoard();
	initTextures();
	initPieces();

	firstClick = true;
	moveMade = false;
	whiteTurn = true;
	check = false;
	checkMate = false;
	AIactive = false;
	checkForCastling = false;
	castlingPossible = false;
	promotionHandled = false;
	staleMate = false;
}

void ChessBoard::initBoard()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if ((i + j) % 2 == 0)
				squares[i-1][j-1] = std::make_shared<Square>(sf::Vector2f(i * SQUARE_SIZE, j * SQUARE_SIZE), WhiteSquare);
			else
				squares[i-1][j-1] = std::make_shared<Square>(sf::Vector2f(i * SQUARE_SIZE, j * SQUARE_SIZE), BlackSquare);
		}
	}
}
void ChessBoard::initTextures()
{
	pieceTextures.insert(std::make_pair("whitePawn", sf::Texture()));
	pieceTextures["whitePawn"].loadFromFile("Textures/Pieces/white_pawn.png");

	pieceTextures.insert(std::make_pair("blackPawn", sf::Texture()));
	pieceTextures["blackPawn"].loadFromFile("Textures/Pieces/black_pawn.png");

	pieceTextures.insert(std::make_pair("whiteRook", sf::Texture()));
	pieceTextures["whiteRook"].loadFromFile("Textures/Pieces/white_rook.png");

	pieceTextures.insert(std::make_pair("blackRook", sf::Texture()));
	pieceTextures["blackRook"].loadFromFile("Textures/Pieces/black_rook.png");

	pieceTextures.insert(std::make_pair("whiteKnight", sf::Texture()));
	pieceTextures["whiteKnight"].loadFromFile("Textures/Pieces/white_knight.png");

	pieceTextures.insert(std::make_pair("blackKnight", sf::Texture()));
	pieceTextures["blackKnight"].loadFromFile("Textures/Pieces/black_knight.png");

	pieceTextures.insert(std::make_pair("whiteBishop", sf::Texture()));
	pieceTextures["whiteBishop"].loadFromFile("Textures/Pieces/white_bishop.png");

	pieceTextures.insert(std::make_pair("blackBishop", sf::Texture()));
	pieceTextures["blackBishop"].loadFromFile("Textures/Pieces/black_bishop.png");

	pieceTextures.insert(std::make_pair("whiteQueen", sf::Texture()));
	pieceTextures["whiteQueen"].loadFromFile("Textures/Pieces/white_queen.png");

	pieceTextures.insert(std::make_pair("blackQueen", sf::Texture()));
	pieceTextures["blackQueen"].loadFromFile("Textures/Pieces/black_queen.png");

	pieceTextures.insert(std::make_pair("whiteKing", sf::Texture()));
	pieceTextures["whiteKing"].loadFromFile("Textures/Pieces/white_king.png");

	pieceTextures.insert(std::make_pair("blackKing", sf::Texture()));
	pieceTextures["blackKing"].loadFromFile("Textures/Pieces/black_king.png");
}

void ChessBoard::initPieces()
{
	for (int i = 0; i < 8; i++)
	{
		auto it1 = pieceTextures.find("whitePawn");
		whitePieces["pawn"].push_back(std::make_shared<Pawn>(it1->second, squares[i][6], 1));
		squares[i][6]->setSquareStatus(Square::WHITE);

		auto it2 = pieceTextures.find("blackPawn");
		blackPieces["pawn"].push_back(std::make_shared<Pawn>(it2->second, squares[i][1], 0));
		squares[i][1]->setSquareStatus(Square::BLACK);
	}
	for (int i = 0; i < 2; i++)
	{
		auto it3 = pieceTextures.find("whiteRook");
		whitePieces["rook"].push_back(std::make_shared<Rook>(it3->second, squares[i * 7][7], 1));
		squares[i*7][7]->setSquareStatus(Square::WHITE);

		auto it4 = pieceTextures.find("blackRook");
		blackPieces["rook"].push_back(std::make_shared<Rook>(it4->second, squares[i * 7][0], 0));
		squares[i*7][0]->setSquareStatus(Square::BLACK);

		auto it5 = pieceTextures.find("whiteKnight");
		whitePieces["knight"].push_back(std::make_shared<Knight>(it5->second, squares[i * 5 + 1][7], 1));
		squares[i * 5 + 1][7]->setSquareStatus(Square::WHITE);

		auto it6 = pieceTextures.find("blackKnight");
		blackPieces["knight"].push_back(std::make_shared<Knight>(it6->second, squares[i * 5 + 1][0], 0));
		squares[i * 5 + 1][0]->setSquareStatus(Square::BLACK);

		auto it7 = pieceTextures.find("whiteBishop");
		whitePieces["bishop"].push_back(std::make_shared<Bishop>(it7->second, squares[i * 3 + 2][7], 1));
		squares[i * 3 + 2][7]->setSquareStatus(Square::WHITE);

		auto it8 = pieceTextures.find("blackBishop");
		blackPieces["bishop"].push_back(std::make_shared<Bishop>(it8->second, squares[i * 3 + 2][0], 0));
		squares[i * 3 + 2][0]->setSquareStatus(Square::BLACK);
	}
	auto it9 = pieceTextures.find("whiteQueen");
	whitePieces["queen"].push_back(std::make_shared<Queen>(it9->second, squares[3][7], 1));
	squares[3][7]->setSquareStatus(Square::WHITE);

	auto it10 = pieceTextures.find("blackQueen");
	blackPieces["queen"].push_back(std::make_shared<Queen>(it10->second, squares[3][0], 0));
	squares[3][0]->setSquareStatus(Square::BLACK);

	auto it11 = pieceTextures.find("whiteKing");
	whitePieces["king"].push_back(std::make_shared<King>(it11->second, squares[4][7], 1));
	squares[4][7]->setSquareStatus(Square::WHITE);

	auto it12 = pieceTextures.find("blackKing");
	blackPieces["king"].push_back(std::make_shared<King>(it12->second, squares[4][0], 0));
	squares[4][0]->setSquareStatus(Square::BLACK);
}

void ChessBoard::render(sf::RenderTarget* Target)
{
	for (auto i = 0; i < 8; i++)
	{
		for (auto j = 0; j < 8; j++)
		{
			squares[i][j]->render(Target);
		}
	}

	for (auto whitePiece : whitePieces)
	{
		for (auto whitePiece : whitePiece.second)
		{
			whitePiece->render(Target);
		}
	}
	for (auto blackPiece : blackPieces)
	{
		for (auto blackPiece : blackPiece.second)
		{
			blackPiece->render(Target);
		}
	}
	Target->draw(promotionWindow);
	for (auto piece : promotionPieces)
	{
		Target->draw(piece);
	}
	Target->draw(promotionWindowOverlay);

	for (auto move : possibleMovesOverlay)
	{
		Target->draw(move);
	}
	for (auto take : possibleTakesOverlay)
	{
		Target->draw(take);
	}
}

void ChessBoard::AImove()
{
	AI.initPieces(blackPieces);

	do
	{
		currentPieceAction = AI.getPiece();
		possibleMoves = currentPieceAction->PossibleMoves(squares);
		possibleTakes = currentPieceAction->PossibleTakes(squares);

		SimulateMove(possibleMoves, currentPieceAction);
		SimulateMove(possibleTakes, currentPieceAction);
	}while(possibleMoves.size() == 0 && possibleTakes.size() == 0);


	std::shared_ptr<Square> moveSquare;

	moveSquare = AI.getMove(possibleMoves, possibleTakes);
	
	if (AI.wasTake())
	{
		currentPieceAction->take(findPiece(moveSquare));
		deletePiece(findPiece(moveSquare));
	}

	currentPieceAction->move(moveSquare);
	if (promotionIsPossible())
	{
		int x = promotedPiece->getSquare()->getPos().x / SQUARE_SIZE - 1;
		int y = promotedPiece->getSquare()->getPos().y / SQUARE_SIZE - 1;
		deletePiece(promotedPiece);
		auto it = pieceTextures.find("blackQueen");
		blackPieces["queen"].push_back(std::make_shared<Queen>(it->second, squares[x][y], 0));
	}

 	whiteTurn = true;

	possibleMoves.clear();
	possibleTakes.clear();
	possibleTakesOverlay.clear();
	possibleMovesOverlay.clear();

}

void ChessBoard::restart()
{
	blackPieces.clear();
	whitePieces.clear();
	possibleMoves.clear();
	possibleTakes.clear();
	possibleTakesOverlay.clear();
	possibleMovesOverlay.clear();
	squares.clear();

	squares.resize(8, std::vector<std::shared_ptr<Square>>(8));

	initBoard();
	initTextures();
	initPieces();

	firstClick = true;
	moveMade = false;
	whiteTurn = true;
	check = false;
	checkMate = false;
	AIactive = false;
	checkForCastling = false;
	castlingPossible = false;
	promotionHandled = false;
	staleMate = false;
}

bool ChessBoard::getCurrentTurn()
{
	return whiteTurn;
}

void ChessBoard::setAI(bool AIactive) 
{
	this->AIactive = AIactive;
}
bool ChessBoard::isAIactive()
{
	return this->AIactive;
}

bool ChessBoard::isMoveMade()
{
	return moveMade;
}