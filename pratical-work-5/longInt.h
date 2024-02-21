/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Header file for the LongInt Class
Note        |   -
Source      |   -
--------------------------- */
#ifndef PRG1_LABO4_LONGINT_SAD_LONGINT_H
#define PRG1_LABO4_LONGINT_SAD_LONGINT_H
#include <vector>
#include <cmath>
#include <iosfwd>
#include <algorithm>

/* ---------------------------
Name        | isPowerOf10
Parameter(s)| T value
Return      | bool
Goal        | Generic function to check if a number is a power of 10
--------------------------- */
template<typename T>
constexpr bool isPowerOf10(T value) {
    while (value > 1) {
        if (value % 10 != 0) {
            return false;
        }
        value /= 10;
    }
    return value == 1;
}

/* ---------------------------
Name        | isNotToBig
Parameter(s)| T value, T radix
Return      | bool
Goal        | Generic function executed at compile time to check if the radix is too big beetwen the value
--------------------------- */
template<typename T>
constexpr bool isNotToBig(T value, T radix) {
    while (value > 1) {
        if (value % radix != 0) {
            return true;
        }
        value /= radix;
    }
    return value == 1;
}

/* ---------------------------
Name        | pow10
Parameter(s)| -
Return      | T
Goal        | Generic function executed at compile time to calculate the power of 10 of a type
--------------------------- */
template<typename T>
constexpr T pow10() {
    T result = 1;
    while (result < std::numeric_limits<T>::max() / 10) {
        result *= 10;
    }
    return result;
}

template<std::unsigned_integral T, T R>
class LongInt;

template<std::unsigned_integral T, T R>
LongInt<T, R> absValue(const LongInt<T, R> &li);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator+ (const LongInt<T, R> &lhs, const LongInt<T,R> &rhs);

template<std::unsigned_integral T, T R>
LongInt<T, R> addValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative);

template<std::unsigned_integral T, T R>
LongInt<T, R> subValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative);

template<std::unsigned_integral T, T R>
LongInt<T, R> multiplyValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator- (const LongInt<T, R> &lhs, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator* (const LongInt<T, R> &lhs, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator+= (LongInt<T, R> &lhs, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator-= (LongInt<T, R> &lhs, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
LongInt<T, R> operator*= (LongInt<T, R> &lhs, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
std::ostream& operator<<(std::ostream &os, const LongInt<T, R> &rhs);

template<std::unsigned_integral T, T R>
std::istream& operator>>(std::istream& is, LongInt<T, R>& li);

template<std::unsigned_integral T, T R>
bool isZero(const LongInt<T, R> &li);

/* ---------------------------
Name        | LongInt
Parameter(s)| T, T R
Return      | -
Goal        | Generic class for the LongInt taking an unsigned integral type and a radix
--------------------------- */
template<std::unsigned_integral T, T R = pow10<T>()>
class LongInt {
public:
    template<std::unsigned_integral T1, T1 R1>
    friend class LongInt;
    static_assert(R > 0, "Radix must be greater than 0");
    static_assert(isNotToBig(std::numeric_limits<T>::max(), R), "Radix is too big");
    static_assert(isPowerOf10(R), "Radix must be a power of 10");
    using digitT = T;
    static const digitT radix = R;
    LongInt() : isNegative(false) {}
    LongInt(T t) {
        if (t < 0) {
            isNegative = true;
            t = -t;
        } else if (t == 0) {
            isNegative = false;
            digits.push_back(0);
        } else {
            isNegative = false;
        }
        while (t > 0) {
            digits.insert(digits.begin(), t % radix);
            t /= radix;
        }
    }
    /* ---------------------------
    Name        | LongInt
    Parameter(s)| const LongInt<T1, R1> &li
    Return      | -
    Goal        | Generic constructor for the LongInt
    --------------------------- */
    template<typename T1, T1 R1>
    explicit LongInt(const LongInt<T1, R1> &li) {
        isNegative = li.isNegative;
        T1 current = 0;
        for (auto it = li.digits.begin(); it != li.digits.end(); ++it) {
            current = current * R1 + *it;
            if (current >= R) {
                digits.push_back(static_cast<T> (current % R));
                current /= R;
            }
        }

        if (current > 0) {
            digits.push_back(static_cast<T> (current));
        }

        std::reverse(digits.begin(), digits.end());
    }

    /* ---------------------------
    Name        | LongInt
    Parameter(s)| -
    Return      | -
    Goal        | Cast LongInt to int
    --------------------------- */
    explicit operator int() const {
        int result = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            result = isNegative ? result - digits[i] * pow(radix, digits.size() - i - 1) : result + digits[i] * pow(radix, digits.size() - i - 1);
        }
        return result;
    }

    /* ---------------------------
    Name        | LongInt
    Parameter(s)| -
    Return      | -
    Goal        | Cast LongInt to long long
    --------------------------- */
    explicit operator long long() const {
        long long result = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            result = isNegative ? result - digits[i] * pow(radix, digits.size() - i - 1) : result + digits[i] * pow(radix, digits.size() - i - 1);
        }
        return result;
    }
    bool operator==(const LongInt &rhs) const;
    bool operator!=(const LongInt &rhs) const;
    bool operator<(const LongInt &rhs) const;
    bool operator>(const LongInt &rhs) const;
    bool operator<=(const LongInt &rhs) const;
    bool operator>=(const LongInt &rhs) const;
    friend LongInt operator+ <> (const LongInt &lhs, const LongInt &rhs);
    friend LongInt operator+= <> (LongInt &lhs, const LongInt &rhs);
    friend LongInt operator- <> (const LongInt &lhs, const LongInt &rhs);
    friend LongInt operator-= <> (LongInt &lhs, const LongInt &rhs);
    friend LongInt operator* <> (const LongInt &lhs, const LongInt &rhs);
    friend LongInt operator*= <> (LongInt &lhs, const LongInt &rhs);
    LongInt & operator++();
    LongInt & operator++(int);
    LongInt & operator--();
    LongInt  &operator--(int);
    friend std::ostream& operator<< <> (std::ostream &os, const LongInt &rhs);
    friend std::istream& operator>> <> (std::istream& is, LongInt& li);

    std::vector<digitT> digits;
private:
    bool isNegative = true;
    friend bool isZero <> (const LongInt &li);
    friend LongInt absValue <> (const LongInt &li);
    friend LongInt addValues <> (const LongInt &lhs,const LongInt &rhs, bool isNegative);
    friend LongInt subValues <> (const LongInt &lhs, const LongInt &rhs, bool isNegative);
    friend LongInt multiplyValues <> (const LongInt &lhs, const LongInt &rhs, bool isNegative);
    void incrementPositive();
    void incrementNegative();
};

#include "longIntImplement.h"

#endif //PRG1_LABO4_LONGINT_SAD_LONGINT_H
