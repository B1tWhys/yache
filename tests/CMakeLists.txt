add_executable(tests
        testFenParsing.cpp
        testPawnPseudoLegalMoveGeneration.cpp
        testCoordinate.cpp
        testMove.cpp
        testKnightPseudoLegalMoveGeneration.cpp
        testRookPseudoLegalMoveGeneration.cpp
        testRookPseudoLegalMoveGeneration.hpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ChessBoard)

catch_discover_tests(tests)
