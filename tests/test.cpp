#include <catch2/catch_test_macros.hpp>
#include "ChessBoard.hpp"

TEST_CASE("ChessBoard initialization")
{
    ChessBoard cb = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
}