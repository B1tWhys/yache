//
// Created by Skyler Arnold on 9/2/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include "Coordinate.hpp"
#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE("Test coordinate get rank and file") {
    auto rank = GENERATE(range(0, 8));
    auto file = GENERATE(range(0, 8));

    Coordinate coordinate = Coordinate(rank, file);
    REQUIRE(coordinate.getRank() == rank);
    REQUIRE(coordinate.getFile() == file);
}

TEST_CASE("Test coordinate init from string") {
    REQUIRE(Coordinate("a1") == Coordinate(0, 0));
    REQUIRE(Coordinate("a8") == Coordinate(7, 0));
    REQUIRE(Coordinate("h1") == Coordinate(0, 7));
    REQUIRE(Coordinate("h8") == Coordinate(7, 7));
}

TEST_CASE("Test coordinate to string") {
    ostringstream stream;

    stream = ostringstream();
    stream << Coordinate(0, 0);
    REQUIRE(stream.str() == "a1");

    stream = ostringstream();
    stream << Coordinate(7, 0);
    REQUIRE(stream.str() == "a8");

    stream = ostringstream();
    stream << Coordinate(0, 7);
    REQUIRE(stream.str() == "h1");

    stream = ostringstream();
    stream << Coordinate(7, 7);
    REQUIRE(stream.str() == "h8");
}