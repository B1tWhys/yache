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

    REQUIRE_FALSE(cb.squareIsOccupied({.rank = rank, .file = file}));
}

TEST_CASE("Initial board state has the right spots occupied") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");

    auto rank = GENERATE(range(0, 8));
    auto file = GENERATE(range(0, 8));

    bool shouldContainPiece = rank < 2 || rank > 5;
    INFO(rank << "," << file << (shouldContainPiece ? " should" : " should not") << " contain a piece");

    REQUIRE(cb.squareIsOccupied({.rank = rank, .file = file}) == shouldContainPiece);
}

TEST_CASE("Turn color is parsed correctly from the fen") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
    REQUIRE(cb.isWhiteTurn);

    cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq -");
    REQUIRE_FALSE(cb.isWhiteTurn);
}

TEST_CASE("Initial board state is parsed correctly") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");

    REQUIRE(cb.squareState({.rank = 0, .file = 0}) == WHITE_ROOK);
    REQUIRE(cb.squareState({.rank = 0, .file = 1}) == WHITE_KNIGHT);
    REQUIRE(cb.squareState({.rank = 0, .file = 2}) == WHITE_BISHOP);
    REQUIRE(cb.squareState({.rank = 0, .file = 3}) == WHITE_QUEEN);
    REQUIRE(cb.squareState({.rank = 0, .file = 4}) == WHITE_KING);
    REQUIRE(cb.squareState({.rank = 0, .file = 5}) == WHITE_BISHOP);
    REQUIRE(cb.squareState({.rank = 0, .file = 6}) == WHITE_KNIGHT);
    REQUIRE(cb.squareState({.rank = 0, .file = 7}) == WHITE_ROOK);

    REQUIRE(cb.squareState({.rank = 1, .file = 0}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 1}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 2}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 3}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 4}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 5}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 6}) == WHITE_PAWN);
    REQUIRE(cb.squareState({.rank = 1, .file = 7}) == WHITE_PAWN);

    REQUIRE(cb.squareState({.rank = 2, .file = 0}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 1}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 2}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 3}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 4}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 5}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 6}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 2, .file = 7}) == EMPTY);

    REQUIRE(cb.squareState({.rank = 3, .file = 0}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 1}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 2}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 3}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 4}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 5}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 6}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 3, .file = 7}) == EMPTY);

    REQUIRE(cb.squareState({.rank = 4, .file = 0}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 1}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 2}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 3}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 4}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 5}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 6}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 4, .file = 7}) == EMPTY);

    REQUIRE(cb.squareState({.rank = 5, .file = 0}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 1}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 2}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 3}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 4}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 5}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 6}) == EMPTY);
    REQUIRE(cb.squareState({.rank = 5, .file = 7}) == EMPTY);

    REQUIRE(cb.squareState({.rank = 6, .file = 0}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 1}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 2}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 3}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 4}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 5}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 6}) == BLACK_PAWN);
    REQUIRE(cb.squareState({.rank = 6, .file = 7}) == BLACK_PAWN);

    REQUIRE(cb.squareState({.rank = 7, .file = 0}) == BLACK_ROOK);
    REQUIRE(cb.squareState({.rank = 7, .file = 1}) == BLACK_KNIGHT);
    REQUIRE(cb.squareState({.rank = 7, .file = 2}) == BLACK_BISHOP);
    REQUIRE(cb.squareState({.rank = 7, .file = 3}) == BLACK_QUEEN);
    REQUIRE(cb.squareState({.rank = 7, .file = 4}) == BLACK_KING);
    REQUIRE(cb.squareState({.rank = 7, .file = 5}) == BLACK_BISHOP);
    REQUIRE(cb.squareState({.rank = 7, .file = 6}) == BLACK_KNIGHT);
    REQUIRE(cb.squareState({.rank = 7, .file = 7}) == BLACK_ROOK);
}

TEST_CASE("En passant fen parsed properly") {
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3");
    REQUIRE(cb.squareState({.rank=2, .file=4}) == BLACK_EN_PASSANT_TARGET);
    cb = ChessBoard("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6");
    REQUIRE(cb.squareState({.rank=5, .file=4}) == WHITE_EN_PASSANT_TARGET);
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