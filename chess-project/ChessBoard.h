#ifndef CHESSBOARD_H
#define CHESSBOARD_H


///
/// Klasa obs³uguj¹ca zdarzenia na szachownicy oraz logike gry
/// 


#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include <map>

#include "ChessAI.h"

class ChessBoard
{
private:
	const sf::Color WhiteSquare = sf::Color(240, 217, 181);
	const sf::Color BlackSquare = sf::Color(181, 136, 99);
	const sf::Color PossibleMove = sf::Color(0, 255, 0, 100); 
	const sf::Color PossibleTake = sf::Color(255, 0, 0, 100);

	bool firstClick;
	bool moveMade;
	bool whiteTurn;
	bool check;
	bool checkMate;
	bool AIactive;
	bool checkForCastling;
	bool castlingPossible;
	bool promotionHandled;
	bool staleMate;

	void initBoard();
	void initTextures();
	void initPieces();

	ChessAI AI;
	std::map<std::string, sf::Texture> pieceTextures;
	std::vector<std::vector<std::shared_ptr<Square>>> squares;

	//zmienne oraz funkcje do obslugi promocji, znajdujace siê w Promotion.cpp
	sf::RectangleShape promotionWindow;
	sf::RectangleShape promotionWindowOverlay;
	std::vector<sf::Sprite> promotionPieces;
	void openPromotionWindow(sf::Vector2f pos);
	void handlePromotion(sf::Event event, sf::Vector2f currentMousePosition);

	//Zmienne figur, oraz metody je obslugujace, znajdujace siê w ChessBoardPieces.cpp
	std::map<std::string, std::vector<std::shared_ptr<Piece>>> whitePieces;
	std::map<std::string, std::vector<std::shared_ptr<Piece>>> blackPieces;
	std::vector<std::shared_ptr<Piece>> takenPieces;
	std::shared_ptr<Piece> currentPieceAction;
	std::shared_ptr<Piece> promotedPiece;
	std::shared_ptr<Piece> findPiece(std::shared_ptr<Square> square);
	void deletePiece(std::shared_ptr<Piece> piece);
	std::shared_ptr<Square> findKing(bool color);

	//Zmienne ruchów, oraz metody je obslugujace, znajdujace siê w ChessBoardMoves.cpp
	std::vector<std::shared_ptr<Square>> possibleTakes;
	std::vector<std::shared_ptr<Square>> possibleMoves;
	std::vector<sf::RectangleShape> possibleTakesOverlay;
	std::vector<sf::RectangleShape> possibleMovesOverlay;
	void showPossibleMovesOverlay(const std::vector<std::shared_ptr<Square>> Moves);
	void showPossibleTakesOverlay(const std::vector<std::shared_ptr<Square>> Takes);
	void SimulateMove(std::vector<std::shared_ptr<Square>> &moves, std::shared_ptr<Piece> piece);

	//Funkcje do obslugi zdarzen, znajdujace siê w ChessBoardEvents.cpp
	void handleFirstClick(sf::Event event, sf::Vector2f currentMousePosition);
	void handleSecondClick(sf::Event event, sf::Vector2f currentMousePosition);

	void Castling(std::shared_ptr<Square> move);

	//Funkcje do obs³ugi szachów, oraz zakonczenia gry, znajdujace siê w ChessBoardEndgame.cpp
	bool checkForBlackCheck();
	bool checkForWhiteCheck();
	void checkForCheckMate();
	void checkForStaleMate();
public:
	ChessBoard();
	virtual ~ChessBoard() = default;

	void handleEvents(sf::Event event, sf::Vector2f currentMousePosition);
	void render(sf::RenderTarget* Target);

	bool getCheckStatus();
	bool getCheckMateStatus();
	bool getStaleMateStatus();
	bool getCurrentTurn();
	bool isAIactive();
	bool isMoveMade();
	bool promotionIsPossible();

	void setAI(bool AIactive);
	void AImove();

	void restart();
};

#endif

