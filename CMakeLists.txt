cmake_minimum_required(VERSION 3.0)

project(yache VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Catch2 3 REQUIRED)
include(CTest)
include(Catch)

# add_executable(yache src/main.cpp)
add_subdirectory(src/ChessBoard)
add_subdirectory(tests)