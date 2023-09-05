//
// Created by Skyler Arnold on 8/26/23.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include "ChessBoard.hpp"
#include "Move.hpp"
#include <iostream>

using namespace Catch::Matchers;

TEST_CASE("Pawns can move forward 1 square") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7| | | | | | | | |
     |6|p| | | | | | | |
     |5| | | | | | | | |
     |4| | | | | | | | |
     |3|P| | | | | | | |
     |2| | | | | | | | |
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/8/p7/8/8/P7/8/8 w - -");
    CAPTURE(cb);
    const Move expectedMove = Move(Coordinate(2, 0), Coordinate(3, 0), EMPTY);
    REQUIRE(vector{expectedMove} == cb.pseudoLegalMoves());
    cb.makeMove(&expectedMove);
    REQUIRE(cb.isWhiteTurn == false);
    REQUIRE(cb.pseudoLegalMoves() == vector{Move(Coordinate(5, 0), Coordinate(4, 0), EMPTY)});
}

TEST_CASE("White pawns properly calculate double forward moves") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7|p| | |p| | | |p|
     |6| | | |p| | | | |
     |5| | | | | | | | |
     |4| | | | | | | | |
     |3| | | |P| | | | |
     |2|P| | |P| | | |P|
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/p2p3p/3p4/8/8/3P4/P2P3P/8 w - -");
    CAPTURE(cb);
    vector<Move> expectedMoves = vector{
            Move(Coordinate("a2"), Coordinate("a4"), EMPTY),
            Move(Coordinate("a2"), Coordinate("a3"), EMPTY),

            Move(Coordinate("d3"), Coordinate("d4"), EMPTY),

            Move(Coordinate("h2"), Coordinate("h4"), EMPTY),
            Move(Coordinate("h2"), Coordinate("h3"), EMPTY),
    };
    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

TEST_CASE("Black pawns properly calculate double forward moves") {
    /*
     | |a|b|c|d|e|f|g|h|
     |-|-|-|-|-|-|-|-|-|
     |8| | | | | | | | |
     |7|p| | |p| | | |p|
     |6| | | |p| | | | |
     |5| | | | | | | | |
     |4| | | | | | | | |
     |3| | | |P| | | | |
     |2|P| | |P| | | |P|
     |1| | | | | | | | |
     */
    ChessBoard cb = ChessBoard("8/p2p3p/3p4/8/8/3P4/P2P3P/8 b - -");
    CAPTURE(cb);
    vector<Move> expectedMoves = vector{
        Move(Coordinate("a7"), Coordinate("a6"), EMPTY),
        Move(Coordinate("a7"), Coordinate("a5"), EMPTY),

        Move(Coordinate("d6"), Coordinate("d5"), EMPTY),

        Move(Coordinate("h7"), Coordinate("h6"), EMPTY),
        Move(Coordinate("h7"), Coordinate("h5"), EMPTY),
    };

    REQUIRE_THAT(cb.pseudoLegalMoves(), UnorderedEquals(expectedMoves));
}

// TODO: en passant, taking, promotion