/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Header for the fibonacci function
Note        |   -
Source      |   -
--------------------------- */
#ifndef PRG1_LABO4_LONGINT_SAD_FIBONACCI_H
#define PRG1_LABO4_LONGINT_SAD_FIBONACCI_H

#include <cstddef>

template<typename T>
T fibonacci(std::size_t pos) {
    T n0 = 0;
    T n1 = 1;
    T new_n = 0;

    if (pos == 1) {
        return n0;
    } else if (pos == 2) {
        return n1;
    } else {
        for (std::size_t i = 2; i <= pos; ++i) {
            new_n = n0 + n1;
            n0 = n1;
            n1 = new_n;
        }
        return new_n;
    }
}

#endif //PRG1_LABO4_LONGINT_SAD_FIBONACCI_H
