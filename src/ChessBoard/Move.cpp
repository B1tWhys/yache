//
// Created by Skyler Arnold on 8/26/23.
//

#include "Move.hpp"

Move::Move(Coordinate from, Coordinate to, SquareState targetSquareState) {
    this->moveBitfield = ((unsigned int) from.cords << 8) | to.cords;
}

Move::Move(const std::string &from, const std::string &to, SquareState targetSquareState):
        Move(Coordinate(from), Coordinate(to), targetSquareState) {}

Move::Move(Coordinate from, char rankOffset, char fileOffset, SquareState targetSquareState):
        Move(from, Coordinate(from.getRank() + rankOffset, from.getFile() + fileOffset), targetSquareState) {}

bool Move::operator==(Move other) const {
    return this->moveBitfield == other.moveBitfield;
}

Coordinate Move::getFromCoordinate() const {
    return Coordinate(this->moveBitfield >> 8);
}

Coordinate Move::getToCoordinate() const {
    return Coordinate(this->moveBitfield & 0xff);
}
