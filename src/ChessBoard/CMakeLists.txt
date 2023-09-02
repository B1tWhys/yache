add_library(ChessBoard
        Coordinate.hpp
        ChessBoard.cpp
        SquareState.hpp
        InvalidFenException.hpp
        CastlingPrivilege.hpp
        Coordinate.cpp
        Move.hpp
        Move.cpp)

target_include_directories(ChessBoard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})