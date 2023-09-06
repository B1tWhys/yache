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

    unsigned char squareToAsciiPiece(Coordinate coordinate) const;

    void addWhitePawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const;
    void addBlackPawnMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const;
    void addKnightMovesFrom(Coordinate coordinate, std::vector<Move> *moves) const;
    void addWhiteRookMovesFrom(Coordinate from, vector<Move> *moves) const;
    void addBlackRookMovesFrom(Coordinate from, vector<Move> *moves) const;
public:
    ChessBoard(const std::string &fen);

    ~ChessBoard();

    bool isWhiteTurn;
    int castlingPrivileges;

    bool squareIsOccupied(Coordinate coordinate) const;

    SquareState squareState(Coordinate coordinate) const;

    std::string boardString() const;

    std::vector<Move> pseudoLegalMoves() const;

    void makeMove(const Move *move);


    friend ostream &operator<<(ostream &output, const ChessBoard &chessBoard) {
        output << chessBoard.boardString();
        return output;
    }
};

#endif