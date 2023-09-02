//
// Created by Skyler Arnold on 9/2/23.
//

#include <catch2/catch_test_macros.hpp>
#include "Move.hpp"
#include "Coordinate.hpp"

TEST_CASE("From coord is correct") {
    Move move = Move(Coordinate("a1"), Coordinate("a2"), EMPTY);
    REQUIRE(move.getFromCoordinate() == Coordinate("a1"));
    REQUIRE(move.getToCoordinate() == Coordinate("a2"));

    move = Move(Coordinate("h7"), Coordinate("a1"), EMPTY);
    REQUIRE(move.getFromCoordinate() == Coordinate("h7"));
    REQUIRE(move.getToCoordinate() == Coordinate("a1"));

    move = Move(Coordinate("a7"), Coordinate("h1"), EMPTY);
    REQUIRE(move.getFromCoordinate() == Coordinate("a7"));
    REQUIRE(move.getToCoordinate() == Coordinate("h1"));
}