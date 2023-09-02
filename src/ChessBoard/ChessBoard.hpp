#ifndef YACHE_CHESSBOARD_HPP
#define YACHE_CHESSBOARD_HPP

#include <string>
#include "Coordinate.hpp"
#include "SquareState.hpp"
#include "Move.hpp"

class Move;

class ChessBoard {
private:
    SquareState board[8][8] = {EMPTY};

    unsigned char squareToAsciiPiece(Coordinate coordinate);
    void addWhitePawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves);
    void addBlackPawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves);
public:
    ChessBoard(const std::string &fen);

    ~ChessBoard();

    bool isWhiteTurn;
    int castlingPrivileges;

    bool squareIsOccupied(Coordinate coordinate);

    SquareState squareState(Coordinate coordinate);

    std::string boardString();

    std::vector<Move> pseudoLegalMoves();

    void makeMove(const Move *move);
};

#endif