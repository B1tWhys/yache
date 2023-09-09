//
// Created by Skyler Arnold on 9/5/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "ChessBoard.hpp"
#include "Move.hpp"
#include "Coordinate.hpp"

using namespace Catch::Matchers;

TEST_CASE("White bishops unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | |B|B| | | |
     |4| | | | | | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/3BB3/8/8/8/8 w - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // light squared bishop
            Move("d5", "a2"),
            Move("d5", "b3"),
            Move("d5", "c4"),
            Move("d5", "e6"),
            Move("d5", "f7"),
            Move("d5", "g8"),
            Move("d5", "c6"),
            Move("d5", "b7"),
            Move("d5", "a8"),
            Move("d5", "e4"),
            Move("d5", "f3"),
            Move("d5", "g2"),
            Move("d5", "h1"),


            // dark squared bishop
            Move("e5", "a1"),
            Move("e5", "b2"),
            Move("e5", "c3"),
            Move("e5", "d4"),
            Move("e5", "f6"),
            Move("e5", "g7"),
            Move("e5", "h8"),

            Move("e5", "b8"),
            Move("e5", "c7"),
            Move("e5", "d6"),
            Move("e5", "f4"),
            Move("e5", "g3"),
            Move("e5", "h2"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("White bishops obstructed by white pawns move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| |P|P| | |P|P| |
     |6| | | | | | | | |
     |5| | | |B|B| | | |
     |4| | | | | | | | |
     |3| |P|P| | |P|P| |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/1PP2PP1/8/3BB3/8/1PP2PP1/8/8 w - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
        // pawn moves
        Move("b7", "b8"),
        Move("c7", "c8"),
        Move("f7", "f8"),
        Move("g7", "g8"),
        Move("b3", "b4"),
        Move("c3", "c4"),
        Move("f3", "f4"),
        Move("g3", "g4"),

        // bishop moves
        Move("d5", "c6"),
        Move("d5", "c4"),
        Move("d5", "e6"),
        Move("d5", "e4"),

        Move("e5", "d6"),
        Move("e5", "d4"),
        Move("e5", "f6"),
        Move("e5", "f4"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("White bishops obstructed by black pawns move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| |p|p| | |p|p| |
     |6| | | | | | | | |
     |5| | | |B|B| | | |
     |4| | | | | | | | |
     |3| |p|p| | |p|p| |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/1pp2pp1/8/3BB3/8/1pp2pp1/8/8 w - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // bishop moves
            Move("d5", "c6"),
            Move("d5", "b7", BLACK_PAWN),
            Move("d5", "c4"),
            Move("d5", "b3", BLACK_PAWN),
            Move("d5", "e6"),
            Move("d5", "f7", BLACK_PAWN),
            Move("d5", "e4"),
            Move("d5", "f3", BLACK_PAWN),

            Move("e5", "d6"),
            Move("e5", "c7", BLACK_PAWN),
            Move("e5", "d4"),
            Move("e5", "c3", BLACK_PAWN),
            Move("e5", "f6"),
            Move("e5", "g3", BLACK_PAWN),
            Move("e5", "f4"),
            Move("e5", "g7", BLACK_PAWN),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black bishops unobstructed move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| | | | | | | | |
     |5| | | |b|b| | | |
     |4| | | | | | | | |
     |3| | | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/8/3bb3/8/8/8/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // light squared bishop
            Move("d5", "a2"),
            Move("d5", "b3"),
            Move("d5", "c4"),
            Move("d5", "e6"),
            Move("d5", "f7"),
            Move("d5", "g8"),
            Move("d5", "c6"),
            Move("d5", "b7"),
            Move("d5", "a8"),
            Move("d5", "e4"),
            Move("d5", "f3"),
            Move("d5", "g2"),
            Move("d5", "h1"),


            // dark squared bishop
            Move("e5", "a1"),
            Move("e5", "b2"),
            Move("e5", "c3"),
            Move("e5", "d4"),
            Move("e5", "f6"),
            Move("e5", "g7"),
            Move("e5", "h8"),

            Move("e5", "b8"),
            Move("e5", "c7"),
            Move("e5", "d6"),
            Move("e5", "f4"),
            Move("e5", "g3"),
            Move("e5", "h2"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black bishops obstructed by black pawns move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6| |p|p| | |p|p| |
     |5| | | | | | | | |
     |4| | | |b|b| | | |
     |3| | | | | | | | |
     |2| |p|p| | |p|p| |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/1pp2pp1/8/3bb3/8/1pp2pp1/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // pawn moves
            Move("b6", "b5"),
            Move("c6", "c5"),
            Move("f6", "f5"),
            Move("g6", "g5"),
            Move("b2", "b1"), // this is gonna break once promotion is implemented...
            Move("c2", "c1"),
            Move("f2", "f1"),
            Move("g2", "g1"),

            // bishop moves
            Move("d4", "c5"),
            Move("d4", "c3"),
            Move("d4", "e5"),
            Move("d4", "e3"),

            Move("e4", "d5"),
            Move("e4", "d3"),
            Move("e4", "f5"),
            Move("e4", "f3"),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black bishops obstructed by white pawns move generation") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| |P|P| | |P|P| |
     |6| | | | | | | | |
     |5| | | |b|b| | | |
     |4| | | | | | | | |
     |3| |P|P| | |P|P| |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/1PP2PP1/8/3bb3/8/1PP2PP1/8/8 b - -");

    INFO("-\n" << cb);
    vector<Move> expectedMoves = vector{
            // bishop moves
            Move("d5", "c6"),
            Move("d5", "b7", WHITE_PAWN),
            Move("d5", "c4"),
            Move("d5", "b3", WHITE_PAWN),
            Move("d5", "e6"),
            Move("d5", "f7", WHITE_PAWN),
            Move("d5", "e4"),
            Move("d5", "f3", WHITE_PAWN),

            Move("e5", "d6"),
            Move("e5", "c7", WHITE_PAWN),
            Move("e5", "d4"),
            Move("e5", "c3", WHITE_PAWN),
            Move("e5", "f6"),
            Move("e5", "g3", WHITE_PAWN),
            Move("e5", "f4"),
            Move("e5", "g7", WHITE_PAWN),
    };

    vector<Move> pseudoLegalMoves = cb.pseudoLegalMoves();

    for (auto expectedMove = expectedMoves.begin(); expectedMove < expectedMoves.end(); expectedMove++) {
        CHECK_THAT(pseudoLegalMoves, VectorContains(*expectedMove));
    }

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}
