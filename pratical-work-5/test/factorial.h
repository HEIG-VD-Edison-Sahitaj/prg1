/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Header for the factorial function
Note        |   -
Source      |   -
--------------------------- */
#ifndef PRG1_LABO4_LONGINT_SAD_FACTORIAL_H
#define PRG1_LABO4_LONGINT_SAD_FACTORIAL_H

#include <cstddef>

template<typename T>
T factorial(std::size_t pos){
    T result = 1;
    if (pos == 0){
        return result;
    } else {
        for (T i = 1; i <= pos; ++i) {
            result *= i;
        }
        return result;
    }
}

#endif //PRG1_LABO4_LONGINT_SAD_FACTORIAL_H
