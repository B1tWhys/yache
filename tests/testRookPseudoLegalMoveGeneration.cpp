//
// Created by Skyler Arnold on 9/2/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "ChessBoard.hpp"
#include "Move.hpp"
#include "Coordinate.hpp"

using namespace Catch::Matchers;

TEST_CASE("White rook unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | | | | | | |
     |4| | | |R| | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/8/3R4/8/8/8 w - -");

    INFO("\n" << cb);
    vector<Move> expectedMoves = vector{
        Move("d4", "d1"),
        Move("d4", "d2"),
        Move("d4", "d3"),
        Move("d4", "d5"),
        Move("d4", "d6"),
        Move("d4", "d7"),
        Move("d4", "d8"),

        Move("d4", "a4"),
        Move("d4", "b4"),
        Move("d4", "c4"),
        Move("d4", "e4"),
        Move("d4", "f4"),
        Move("d4", "g4"),
        Move("d4", "h4"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("White rook obstructed by white pieces") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | |N| | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| |P| |R| |P| | |
     |4| | | | | | | | |
     |3| | | |P| | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("3N4/8/8/1P1R1P2/8/3P4/8/8 w - -");
    INFO("\n" << cb);
    vector<Move> expectedMoves = vector{
        // pawn moves. not really related to the rook
        Move("d3", "d4"),
        Move("b5", "b6"),
        Move("f5", "f6"),

        // knight moves
        Move("d8", "b7"),
        Move("d8", "c6"),
        Move("d8", "e6"),
        Move("d8", "f7"),

        // rook moves
        Move("d5", "d6"),
        Move("d5", "d7"),
        Move("d5", "d4"),
        Move("d5", "c5"),
        Move("d5", "e5")
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("White rook obstructed by black pieces") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | |n| | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| |p| |R| |p| | |
     |4| | | | | | | | |
     |3| | | |p| | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("3n4/8/8/1p1R1p2/8/3p4/8/8 w - -");
    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // vertical
            Move("d5", "d8", BLACK_KNIGHT),
            Move("d5", "d7", EMPTY),
            Move("d5", "d6", EMPTY),
            Move("d5", "d4", EMPTY),
            Move("d5", "d3", BLACK_PAWN),

            // horizontal
            Move("d5", "c5", EMPTY),
            Move("d5", "b5", BLACK_PAWN),
            Move("d5", "e5", EMPTY),
            Move("d5", "f5", BLACK_PAWN),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black rook unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | | | | | | |
     |4| | | |R| | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/8/3r4/8/8/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            Move("d4", "d1"),
            Move("d4", "d2"),
            Move("d4", "d3"),
            Move("d4", "d5"),
            Move("d4", "d6"),
            Move("d4", "d7"),
            Move("d4", "d8"),

            Move("d4", "a4"),
            Move("d4", "b4"),
            Move("d4", "c4"),
            Move("d4", "e4"),
            Move("d4", "f4"),
            Move("d4", "g4"),
            Move("d4", "h4"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black rook obstructed by black pieces") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | |n| | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| |p| |r| |p| | |
     |4| | | | | | | | |
     |3| | | |p| | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("3n4/8/8/1p1r1p2/8/3p4/8/8 b - -");
    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // pawn moves. not really related to the rook
            Move("d3", "d2"),
            Move("b5", "b4"),
            Move("f5", "f4"),

            // knight moves
            Move("d8", "b7"),
            Move("d8", "c6"),
            Move("d8", "e6"),
            Move("d8", "f7"),

            // rook moves
            Move("d5", "d6"),
            Move("d5", "d7"),
            Move("d5", "d4"),
            Move("d5", "c5"),
            Move("d5", "e5")
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black rook obstructed by white pieces") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | |N| | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| |P| |r| |P| | |
     |4| | | | | | | | |
     |3| | | |P| | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("3N4/8/8/1P1r1P2/8/3P4/8/8 b - -");
    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // vertical
            Move("d5", "d8", BLACK_KNIGHT),
            Move("d5", "d7", EMPTY),
            Move("d5", "d6", EMPTY),
            Move("d5", "d4", EMPTY),
            Move("d5", "d3", BLACK_PAWN),

            // horizontal
            Move("d5", "c5", EMPTY),
            Move("d5", "b5", BLACK_PAWN),
            Move("d5", "e5", EMPTY),
            Move("d5", "f5", BLACK_PAWN),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}