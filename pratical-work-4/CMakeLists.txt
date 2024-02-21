cmake_minimum_required(VERSION 3.27)
project(prg1_labo4_longint_sad)

set(CMAKE_CXX_STANDARD 14)

include_directories(test)
include_directories(type)

add_executable(prg1_labo4_a061084_sad
        executables/a061084.cpp
        longInt.cpp)

add_executable(prg1_labo4_factorial_sad
        executables/factorial.cpp
        longInt.cpp)

add_executable(prg1_labo4_fibonacci_sad
        executables/fibonacci.cpp
        longInt.cpp)

add_executable(prg1_labo4_longint_sad
        main.cpp
        longInt.cpp)
