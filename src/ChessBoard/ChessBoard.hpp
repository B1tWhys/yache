#ifndef _YACHE_CB_CHESS_BOARD
#define _YACHE_CB_CHESS_BOARD

#include <string>
#include "Coordinate.hpp"
#include "SquareState.hpp"

class ChessBoard {
private:
    SquareState board[8][8] = {EMPTY};

    unsigned char squareToAsciiPiece(Coordinate coordinate);

public:
    ChessBoard(const std::string &fen);

    ~ChessBoard();

    bool isWhiteTurn;
    int castlingPrivileges;

    bool squareIsOccupied(Coordinate coordinate);

    SquareState squareState(Coordinate coordinate);

    std::string boardString();
};

#endif