cmake_minimum_required(VERSION 3.25)
project(L4_Snake_game)

set(CMAKE_CXX_STANDARD 20)
add_executable(Snake main.cpp console_io.cpp
        game.cpp
        game.h)