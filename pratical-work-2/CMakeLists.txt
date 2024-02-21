cmake_minimum_required(VERSION 3.26)
project(prg1_labo3_mss)

set(CMAKE_CXX_STANDARD 20)

add_executable(prg1_labo3_mss main.cpp
        files/fileReader.cpp
        files/fileReader.h
        display/showResult.cpp
        display/showResult.h
        formules/formules.cpp
        formules/formules.h)
