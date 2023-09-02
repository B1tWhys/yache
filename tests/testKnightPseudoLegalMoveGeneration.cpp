//
// Created by Skyler Arnold on 9/2/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "ChessBoard.hpp"
#include "Move.hpp"
#include "Coordinate.hpp"

using namespace Catch::Matchers;

TEST_CASE("White knight move generation 1") {
    ChessBoard cb = ChessBoard("8/8/8/3N4/8/8/8/8 w - -");
    vector<Move> expectedMoves = vector{
        Move(Coordinate("d5"), Coordinate("c3"), EMPTY),
        Move(Coordinate("d5"), Coordinate("e3"), EMPTY),
        Move(Coordinate("d5"), Coordinate("f4"), EMPTY),
        Move(Coordinate("d5"), Coordinate("f6"), EMPTY),
        Move(Coordinate("d5"), Coordinate("e7"), EMPTY),
        Move(Coordinate("d5"), Coordinate("c7"), EMPTY),
        Move(Coordinate("d5"), Coordinate("b6"), EMPTY),
        Move(Coordinate("d5"), Coordinate("b4"), EMPTY),
    };
    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("White knight move generation 2") {
    ChessBoard cb = ChessBoard("N6N/8/8/8/8/8/8/N6N w - -");
    vector<Move> expectedMoves = vector{
        Move(Coordinate("a8"), Coordinate("c7"), EMPTY),
        Move(Coordinate("a8"), Coordinate("b6"), EMPTY),

        Move(Coordinate("h8"), Coordinate("f7"), EMPTY),
        Move(Coordinate("h8"), Coordinate("g6"), EMPTY),

        Move(Coordinate("h1"), Coordinate("g3"), EMPTY),
        Move(Coordinate("h1"), Coordinate("f2"), EMPTY),

        Move(Coordinate("a1"), Coordinate("c2"), EMPTY),
        Move(Coordinate("a1"), Coordinate("b3"), EMPTY),
    };
    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black knight move generation 1") {
    ChessBoard cb = ChessBoard("8/8/8/3n4/8/8/8/8 b - -");
    vector<Move> expectedMoves = vector{
            Move(Coordinate("d5"), Coordinate("c3"), EMPTY),
            Move(Coordinate("d5"), Coordinate("e3"), EMPTY),
            Move(Coordinate("d5"), Coordinate("f4"), EMPTY),
            Move(Coordinate("d5"), Coordinate("f6"), EMPTY),
            Move(Coordinate("d5"), Coordinate("e7"), EMPTY),
            Move(Coordinate("d5"), Coordinate("c7"), EMPTY),
            Move(Coordinate("d5"), Coordinate("b6"), EMPTY),
            Move(Coordinate("d5"), Coordinate("b4"), EMPTY),
    };
    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black knight move generation 2") {
    ChessBoard cb = ChessBoard("n6n/8/8/8/8/8/8/n6n b - -");
    vector<Move> expectedMoves = vector{
            Move(Coordinate("a8"), Coordinate("c7"), EMPTY),
            Move(Coordinate("a8"), Coordinate("b6"), EMPTY),

            Move(Coordinate("h8"), Coordinate("f7"), EMPTY),
            Move(Coordinate("h8"), Coordinate("g6"), EMPTY),

            Move(Coordinate("h1"), Coordinate("g3"), EMPTY),
            Move(Coordinate("h1"), Coordinate("f2"), EMPTY),

            Move(Coordinate("a1"), Coordinate("c2"), EMPTY),
            Move(Coordinate("a1"), Coordinate("b3"), EMPTY),
    };
    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}
