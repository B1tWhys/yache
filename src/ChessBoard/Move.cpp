//
// Created by Skyler Arnold on 8/26/23.
//

#include "Move.hpp"

Move::Move(Coordinate from, Coordinate to, SquareState targetSquareState) {
    this->moveBitfield = ((unsigned int) from.cords << 8) | to.cords;
}

bool Move::operator==(Move other) const {
    return this->moveBitfield == other.moveBitfield;
}

Coordinate Move::getFromCoordinate() const {
    return Coordinate(this->moveBitfield >> 8);
}

Coordinate Move::getToCoordinate() const {
    return Coordinate(this->moveBitfield & 0xff);
}
