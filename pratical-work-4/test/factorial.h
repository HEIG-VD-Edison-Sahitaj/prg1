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
