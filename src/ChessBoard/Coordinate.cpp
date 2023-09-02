//
// Created by Skyler Arnold on 8/26/23.
//

#include "Coordinate.hpp"

Coordinate::Coordinate(unsigned char rank, unsigned char file) {
    cords = rank << 4 | (file & 0xf);
}

Coordinate::Coordinate(unsigned char cords) {
    this->cords = cords;
}

Coordinate::Coordinate(const std::string &notation): Coordinate(notation[1] - 'a', notation[0] - '1') {
}

unsigned char Coordinate::getRank() const {
    return cords >> 4;
}

unsigned char Coordinate::getFile() const {
    return cords & 0x0f;
}

bool Coordinate::isValidSquare() const {
    return getRank() < 8 && getFile() < 8;
}

bool Coordinate::operator==(const Coordinate other) const {
    return other.cords == cords;
}