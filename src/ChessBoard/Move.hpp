//
// Created by Skyler Arnold on 8/26/23.
//

#ifndef YACHE_MOVE_HPP
#define YACHE_MOVE_HPP

#include "Coordinate.hpp"
#include "SquareState.hpp"
#include "ChessBoard.hpp"
#include <iostream>

class ChessBoard;

using namespace std;

class Move {
public:
    Move(Coordinate from, Coordinate to, SquareState targetSquareState);
    Coordinate getFromCoordinate() const;
    Coordinate getToCoordinate() const;
    bool operator ==(Move other) const;
    friend ostream &operator<<(ostream &output, const Move &move) {
        output << "from: " << move.getFromCoordinate() << " to: " << move.getToCoordinate();
        return output;
    }
private:
    unsigned int moveBitfield;
//    SquareState targetSquareState;
};


#endif //YACHE_MOVE_HPP
