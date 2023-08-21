add_library(ChessBoard ChessBoard.cpp
        Coordinate.hpp
        SquareState.hpp
        InvalidFenException.hpp
        CastlingPrivilege.hpp)

target_include_directories(ChessBoard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})