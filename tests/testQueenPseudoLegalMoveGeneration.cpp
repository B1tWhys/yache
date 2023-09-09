//
// Created by Skyler Arnold on 9/7/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "ChessBoard.hpp"
#include "Move.hpp"
#include "Coordinate.hpp"

using namespace Catch::Matchers;

TEST_CASE("Test white queen unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | |Q| | | | |
     |4| | | | | | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/3Q4/8/8/8/8 w - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
        Move("d5", "d6"),
        Move("d5", "d7"),
        Move("d5", "d8"),
        Move("d5", "d4"),
        Move("d5", "d3"),
        Move("d5", "d2"),
        Move("d5", "d1"),
        Move("d5", "c5"),
        Move("d5", "b5"),
        Move("d5", "a5"),
        Move("d5", "e5"),
        Move("d5", "f5"),
        Move("d5", "g5"),
        Move("d5", "h5"),

        Move("d5", "e6"),
        Move("d5", "f7"),
        Move("d5", "g8"),
        Move("d5", "c4"),
        Move("d5", "b3"),
        Move("d5", "a2"),

        Move("d5", "c6"),
        Move("d5", "b7"),
        Move("d5", "a8"),
        Move("d5", "e4"),
        Move("d5", "f3"),
        Move("d5", "g2"),
        Move("d5", "h1"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Test white queen move generation obstructed by white pawns") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| |P| |P| |P| | |
     |6| | | | | | | | |
     |5| |P| |Q| |P| | |
     |4| | | | | | | | |
     |3| |P| |P| |P| | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/1P1P1P2/8/1P1Q1P2/8/1P1P1P2/8/8 w - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // pawn moves
            Move("b7", "b8"),
            Move("d7", "d8"),
            Move("f7", "f8"),
            Move("b5", "b6"),
            Move("f5", "f6"),
            Move("b3", "b4"),
            Move("d3", "d4"),
            Move("f3", "f4"),

            Move("d5", "d6"),
            Move("d5", "d4"),
            Move("d5", "c5"),
            Move("d5", "e5"),
            Move("d5", "e6"),
            Move("d5", "c4"),
            Move("d5", "c6"),
            Move("d5", "e4"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Test black queen unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | |q| | | | |
     |4| | | | | | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/3q4/8/8/8/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            Move("d5", "d6"),
            Move("d5", "d7"),
            Move("d5", "d8"),
            Move("d5", "d4"),
            Move("d5", "d3"),
            Move("d5", "d2"),
            Move("d5", "d1"),
            Move("d5", "c5"),
            Move("d5", "b5"),
            Move("d5", "a5"),
            Move("d5", "e5"),
            Move("d5", "f5"),
            Move("d5", "g5"),
            Move("d5", "h5"),

            Move("d5", "e6"),
            Move("d5", "f7"),
            Move("d5", "g8"),
            Move("d5", "c4"),
            Move("d5", "b3"),
            Move("d5", "a2"),

            Move("d5", "c6"),
            Move("d5", "b7"),
            Move("d5", "a8"),
            Move("d5", "e4"),
            Move("d5", "f3"),
            Move("d5", "g2"),
            Move("d5", "h1"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Test black queen move generation obstructed by black pawns") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| |p| |p| |p| | |
     |6| | | | | | | | |
     |5| |p| |q| |p| | |
     |4| | | | | | | | |
     |3| |p| |p| |p| | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/1p1p1p2/8/1p1q1p2/8/1p1p1p2/8/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // pawn moves
            Move("b7", "b6"),
            Move("d7", "d6"),
            Move("f7", "f6"),
            Move("b5", "b4"),
            Move("f5", "f4"),
            Move("b3", "b2"),
            Move("d3", "d2"),
            Move("f3", "f2"),

            Move("d5", "d6"),
            Move("d5", "d4"),
            Move("d5", "c5"),
            Move("d5", "e5"),
            Move("d5", "e6"),
            Move("d5", "c4"),
            Move("d5", "c6"),
            Move("d5", "e4"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}
