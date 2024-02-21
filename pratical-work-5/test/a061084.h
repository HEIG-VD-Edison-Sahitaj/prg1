/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Header for the a061084 function
Note        |   -
Source      |   -
--------------------------- */
#ifndef PRG1_LABO4_LONGINT_SAD_A061084_H
#define PRG1_LABO4_LONGINT_SAD_A061084_H

#include <cstddef>

template<typename T>
T a061084(std::size_t pos) {
    T n0 = 1;
    T n1 = 2;
    T new_n = 0;

    if (pos == 0) {
        return n0;
    } else if (pos == 1) {
        return n1;
    } else {
        for (std::size_t i = 1; i < pos; ++i) {
            new_n = n0 - n1;
            n0 = n1;
            n1 = new_n;
        }
        return new_n;
    }
}

#endif //PRG1_LABO4_LONGINT_SAD_A061084_H
