cmake_minimum_required(VERSION 3.27)
project(prg1_labo5b_longint_sad)

set(CMAKE_CXX_STANDARD 23)

include_directories(test)
include_directories(type)

add_executable(prg1_labo5b_a061084_sad
        executables/a061084.cpp
)

add_executable(prg1_labo5b_factorial_sad
        executables/factorial.cpp
)

add_executable(prg1_labo5b_fibonacci_sad
        executables/fibonacci.cpp
)

add_executable(prg1_labo5b_longint_sad
        main.cpp)
