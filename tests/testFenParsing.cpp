#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include "ChessBoard.hpp"
#include "CastlingPrivilege.hpp"

TEST_CASE("Empty board returns false for any square being occupied")
{
    ChessBoard cb = ChessBoard("8/8/8/8/8/8/8/8 w - -");
    auto rank = GENERATE(range(0, 8));
    auto file = GENERATE(range(0, 8));

    INFO("Testing rank: " << rank << " file: " << file);

    REQUIRE_FALSE(cb.squareIsOccupied(Coordinate(rank, file)));
}

TEST_CASE("Initial board state has the right spots occupied") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");

    auto rank = GENERATE(range(0, 8));
    auto file = GENERATE(range(0, 8));

    bool shouldContainPiece = rank < 2 || rank > 5;
    INFO(rank << "," << file << (shouldContainPiece ? " should" : " should not") << " contain a piece");

    REQUIRE(cb.squareIsOccupied(Coordinate(rank, file)) == shouldContainPiece);
}

TEST_CASE("Turn color is parsed correctly from the fen") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    REQUIRE(cb.isWhiteTurn);

    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -");
    REQUIRE_FALSE(cb.isWhiteTurn);
}

TEST_CASE("Initial board state is parsed correctly") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");

    REQUIRE(cb.squareState(Coordinate(0, 0)) == WHITE_ROOK);
    REQUIRE(cb.squareState(Coordinate(0, 1)) == WHITE_KNIGHT);
    REQUIRE(cb.squareState(Coordinate(0, 2)) == WHITE_BISHOP);
    REQUIRE(cb.squareState(Coordinate(0, 3)) == WHITE_QUEEN);
    REQUIRE(cb.squareState(Coordinate(0, 4)) == WHITE_KING);
    REQUIRE(cb.squareState(Coordinate(0, 5)) == WHITE_BISHOP);
    REQUIRE(cb.squareState(Coordinate(0, 6)) == WHITE_KNIGHT);
    REQUIRE(cb.squareState(Coordinate(0, 7)) == WHITE_ROOK);

    REQUIRE(cb.squareState(Coordinate(1, 0)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 1)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 2)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 3)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 4)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 5)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 6)) == WHITE_PAWN);
    REQUIRE(cb.squareState(Coordinate(1, 7)) == WHITE_PAWN);

    REQUIRE(cb.squareState(Coordinate(2, 0)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 1)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 2)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 3)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 4)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 5)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 6)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(2, 7)) == EMPTY);

    REQUIRE(cb.squareState(Coordinate(3, 0)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 1)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 2)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 3)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 4)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 5)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 6)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(3, 7)) == EMPTY);

    REQUIRE(cb.squareState(Coordinate(4, 0)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 1)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 2)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 3)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 4)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 5)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 6)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(4, 7)) == EMPTY);

    REQUIRE(cb.squareState(Coordinate(5, 0)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 1)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 2)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 3)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 4)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 5)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 6)) == EMPTY);
    REQUIRE(cb.squareState(Coordinate(5, 7)) == EMPTY);

    REQUIRE(cb.squareState(Coordinate(6, 0)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 1)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 2)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 3)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 4)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 5)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 6)) == BLACK_PAWN);
    REQUIRE(cb.squareState(Coordinate(6, 7)) == BLACK_PAWN);

    REQUIRE(cb.squareState(Coordinate(7, 0)) == BLACK_ROOK);
    REQUIRE(cb.squareState(Coordinate(7, 1)) == BLACK_KNIGHT);
    REQUIRE(cb.squareState(Coordinate(7, 2)) == BLACK_BISHOP);
    REQUIRE(cb.squareState(Coordinate(7, 3)) == BLACK_QUEEN);
    REQUIRE(cb.squareState(Coordinate(7, 4)) == BLACK_KING);
    REQUIRE(cb.squareState(Coordinate(7, 5)) == BLACK_BISHOP);
    REQUIRE(cb.squareState(Coordinate(7, 6)) == BLACK_KNIGHT);
    REQUIRE(cb.squareState(Coordinate(7, 7)) == BLACK_ROOK);
}

TEST_CASE("En passant fen parsed properly") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3");
    REQUIRE(cb.squareState(Coordinate(2, 4)) == BLACK_EN_PASSANT_TARGET);
    cb = ChessBoard("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6");
    REQUIRE(cb.squareState(Coordinate(5, 4)) == WHITE_EN_PASSANT_TARGET);
}

TEST_CASE("Exception thrown on invalid FEN") {
    REQUIRE_THROWS(ChessBoard("rnbqkbnr/pppppppp/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"));
    REQUIRE_THROWS(ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR W KQkq -"));
    REQUIRE_THROWS(ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR KQkq -"));
    REQUIRE_THROWS(ChessBoard("anbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"));
}

TEST_CASE("Pretty printing the board works") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    std::string correct_ascii = "| |a|b|c|d|e|f|g|h|\n"
                                "|-|-|-|-|-|-|-|-|-|\n"
                                "|8|r|n|b|q|k|b|n|r|\n"
                                "|7|p|p|p|p|p|p|p|p|\n"
                                "|6| | | | | | | | |\n"
                                "|5| | | | | | | | |\n"
                                "|4| | | | | | | | |\n"
                                "|3| | | | | | | | |\n"
                                "|2|P|P|P|P|P|P|P|P|\n"
                                "|1|R|N|B|Q|K|B|N|R|\n";
    REQUIRE(cb.boardString() == correct_ascii);
}

TEST_CASE("Castling is parsed properly") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - -");
    REQUIRE(cb.castlingPrivileges == 0);
    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w K -");
    REQUIRE(cb.castlingPrivileges == WHITE_KING_SIDE);
    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w k -");
    REQUIRE(cb.castlingPrivileges == BLACK_KING_SIDE);
    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Q -");
    REQUIRE(cb.castlingPrivileges == WHITE_QUEEN_SIDE);
    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w q -");
    REQUIRE(cb.castlingPrivileges == BLACK_QUEEN_SIDE);
    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    REQUIRE(cb.castlingPrivileges == (WHITE_QUEEN_SIDE | WHITE_KING_SIDE | BLACK_KING_SIDE | BLACK_QUEEN_SIDE));
}