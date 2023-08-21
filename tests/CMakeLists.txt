add_executable(tests testFenParsing.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ChessBoard)

catch_discover_tests(tests)
