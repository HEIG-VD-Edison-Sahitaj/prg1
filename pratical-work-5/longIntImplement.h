/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   23.01.2024 (2359)
Goal        |   Second header file for the LongInt Class
Note        |   -
Source      |   -
--------------------------- */
#ifndef LONGINTIMPLEMENT_H
#define LONGINTIMPLEMENT_H

#include <sstream>
#include <iostream>
#include "iomanip"

/* ---------------------------
Name        | isZero
Parameter(s)| LongInt<T, R> &li
Return      | bool
Goal        | Generic function to check if a LongInt has a value of 0
--------------------------- */
template<std::unsigned_integral T, T R>
bool isZero(LongInt<T, R> &li) {
    bool result = true;
    for (auto value: li.digits) {
        if (value != 0) {
            return false;
        }
    }
    return result;
}

/* ---------------------------
Name        | absValue
Parameter(s)| LongInt<T, R> &li
Return      | LongInt<T, R>
Goal        | Generic function to get the absolute value of a LongInt
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> absValue(const LongInt<T, R> &li) {
    LongInt<T, R> result = li;
    result.isNegative = false;
    return result;
}

/* ---------------------------
Name        | addValues
Parameter(s)| const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative
Return      | LongInt<T, R>
Goal        | Generic function to add two LongInts
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> addValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative) {
    LongInt<T, R> result;
    const auto &longer = lhs.digits.size() >= rhs.digits.size() ? lhs.digits : rhs.digits;

    int carry = 0;
    // Loop through the longer vector and add the digits of the shorter vector
    for (size_t i = 0; i < longer.size(); ++i) {
        int digit = carry;
        // If the index is smaller than the size of the vector, add the digit of the vector to the digit variable
        if (i < lhs.digits.size()) {
            digit += lhs.digits[lhs.digits.size() - 1 - i];
        }
        if (i < rhs.digits.size()) {
            digit += rhs.digits[rhs.digits.size() - 1 - i];
        }
        result.digits.insert(result.digits.begin(), digit % LongInt<T, R>::radix);
        carry = digit / LongInt<T, R>::radix;
    }

    // If there is a carry left, add it to the vector
    if (carry) {
        result.digits.insert(result.digits.begin(), carry);
    }
    result.isNegative = isNegative;
    if (isZero(result)) {
        return LongInt<T, R>(0);
    }
    return result;
}

/* ---------------------------
Name        | subValues
Parameter(s)| const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative
Return      | LongInt<T, R>
Goal        | Generic function to subtract two LongInts (same logic as addValues, but minor modifications)
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> subValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative) {
    LongInt<T, R> result;
    const auto &longer = lhs.digits.size() >= rhs.digits.size() ? lhs.digits : rhs.digits;

    int carry = 0;
    for (size_t i = 0; i < longer.size(); ++i) {
        int digit = carry;
        if (i < lhs.digits.size()) {
            digit += lhs.digits[lhs.digits.size() - 1 - i];
        }
        if (i < rhs.digits.size()) {
            digit -= rhs.digits[rhs.digits.size() - 1 - i];
        }
        if (digit < 0) {
            digit += LongInt<T, R>::radix;
            carry = -1;
        } else {
            carry = 0;
        }
        result.digits.insert(result.digits.begin(), digit);
    }

    if (carry) {
        result.digits.insert(result.digits.begin(), carry);
    }

    // Remove leading zeros
    while (!result.digits.empty() && result.digits[0] == 0) {
        result.digits.erase(result.digits.begin());
    }

    result.isNegative = isNegative;
    if (isZero(result)) {
        return LongInt<T, R>(0);
    }
    return result;
}

/* ---------------------------
Name        | multiplyValues
Parameter(s)| const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative
Return      | LongInt<T, R>
Goal        | Generic function to multiply two LongInts
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> multiplyValues(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs, bool isNegative) {
    LongInt<T, R> result;
    for (size_t i = 0; i < rhs.digits.size(); ++i) {
        // Temporary LongInt to store the result of the multiplication of the current digit of the rhs with the lhs
        LongInt<T, R> temp;
        int carry = 0;
        for (size_t j = 0; j < lhs.digits.size(); ++j) {
            // Value of the multiplication of the current digit of the rhs with the lhs
            int digit = rhs.digits[rhs.digits.size() - 1 - i] * lhs.digits[lhs.digits.size() - 1 - j] + carry;
            temp.digits.insert(temp.digits.begin(), digit % LongInt<T, R>::radix);
            carry = digit / LongInt<T, R>::radix;
        }
        if (carry) {
            temp.digits.insert(temp.digits.begin(), carry);
        }

        for (size_t k = 0; k < i; ++k) {
            temp.digits.push_back(0);
        }
        result = addValues(result, temp, false);
    }
    result.isNegative = isNegative;
    if (isZero(result)) {
        return LongInt<T, R>(0);
    }
    return result;
}

/* ---------------------------
Name        | operator==
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if two LongInts are equal
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator==(const LongInt &rhs) const {
    if (isNegative && rhs.isNegative) {
        return false;
    }
    if (digits.size() != rhs.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}

/* ---------------------------
Name        | operator!=
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if two LongInts are not equal
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator!=(const LongInt &rhs) const {
    return !(*this == rhs);
}

/* ---------------------------
Name        | operator<
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if a LongInt is smaller than another LongInt
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator<(const LongInt &rhs) const {
    if (isNegative && !rhs.isNegative) {
        return true;
    }
    if (!isNegative && rhs.isNegative) {
        return false;
    }
    if (isNegative && rhs.isNegative) {
        if (digits.size() > rhs.digits.size()) {
            return true;
        }
        if (digits.size() < rhs.digits.size()) {
            return false;
        }
        for (int i = 0; i < digits.size(); ++i) {
            if (digits[i] > rhs.digits[i]) {
                return true;
            }
            if (digits[i] < rhs.digits[i]) {
                return false;
            }
        }
        return false;
    }
    if (digits.size() < rhs.digits.size()) {
        return true;
    }
    if (digits.size() > rhs.digits.size()) {
        return false;
    }
    for (int i = 0; i < digits.size(); ++i) {
        if (digits[i] < rhs.digits[i]) {
            return true;
        }
        if (digits[i] > rhs.digits[i]) {
            return false;
        }
    }
    return false;
}

/* ---------------------------
Name        | operator>
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if a LongInt is greater than another LongInt using the operator<
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator>(const LongInt &rhs) const {
    return rhs < *this;
}

/* ---------------------------
Name        | operator<=
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if a LongInt is smaller or equal than another LongInt using the operator< and operator==
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator<=(const LongInt &rhs) const {
    return !(rhs < *this) || rhs == *this;
}

/* ---------------------------
Name        | operator>=
Parameter(s)| const LongInt &rhs
Return      | bool
Goal        | Generic operator to check if a LongInt is greater or equal than another LongInt using the operator< and operator==
--------------------------- */
template<std::unsigned_integral T, T R>
bool LongInt<T, R>::operator>=(const LongInt &rhs) const {
    return !(*this < rhs) || rhs == *this;
}

/* ---------------------------
Name        | operator+
Parameter(s)| cons LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to add two LongInt checking the sign of the LongInts and using addValues and subValues
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator+(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, false);
        }
        return subValues(lhs, rhs, true);
    }
    if (!lhs.isNegative && rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, true);
        }
        return subValues(lhs, rhs, false);
    }
    if (lhs.isNegative && rhs.isNegative) {
        return addValues(lhs, rhs, true);
    }
    return addValues(lhs, rhs, false);
}

/* ---------------------------
Name        | operator+=
Parameter(s)| LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to add two LongInt using the operator+ and assigning the result to the lhs
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator+=(LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    lhs = lhs + rhs;
    return lhs;
}

/* ---------------------------
Name        | operator-
Parameter(s)| const LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to subtract two LongInt checking the sign of the LongInts and using addValues and subValues
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator-(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        return addValues(lhs, rhs, true);
    }
    if (!lhs.isNegative && rhs.isNegative) {
        return addValues(lhs, rhs, false);
    }
    if (lhs.isNegative && rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, false);
        }
        return subValues(lhs, rhs, true);
    }
    if (absValue(lhs) < absValue(rhs)) {
        return subValues(rhs, lhs, true);
    }
    return subValues(lhs, rhs, false);
}

/* ---------------------------
Name        | operator-=
Parameter(s)| LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to subtract two LongInt using the operator- and assigning the result to the lhs
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator-=(LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    lhs = lhs - rhs;
    return lhs;
}

/* ---------------------------
Name        | operator*
Parameter(s)| LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to multiply two LongInt checking the sign of the LongInts and using multiplyValues
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator*(const LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        return multiplyValues(lhs, rhs, true);
    }
    if (!lhs.isNegative && rhs.isNegative) {
        return multiplyValues(lhs, rhs, true);
    }
    if (lhs.isNegative && rhs.isNegative) {
        return multiplyValues(lhs, rhs, false);
    }
    return multiplyValues(lhs, rhs, false);
}

/* ---------------------------
Name        | operator*=
Parameter(s)| LongInt<T, R> &lhs, const LongInt<T, R> &rhs
Return      | LongInt<T, R>
Goal        | Generic operator to multiply two LongInt using the operator* and assigning the result to the lhs
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> operator*=(LongInt<T, R> &lhs, const LongInt<T, R> &rhs) {
    lhs = lhs * rhs;
    return lhs;
}

/* ---------------------------
Name        | operator++
Parameter(s)| -
Return      | LongInt<T, R>
Goal        | Generic operator to pre-incrementing (++x) a LongInt using incrementPositive and incrementNegative
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> &LongInt<T, R>::operator++() {
    if (!isNegative) {
        incrementPositive();
    } else {
        incrementNegative();
    }
    return *this;
}

/* ---------------------------
Name        | operator++
Parameter(s)| int
Return      | LongInt<T, R>
Goal        | Generic operator to post-incrementing (x++) a LongInt using operator++ and assigning the result to the lhs
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> &LongInt<T, R>::operator++(int) {
    return ++(*this);
}

/* ---------------------------
Name        | operator--
Parameter(s)| -
Return      | LongInt<T, R>
Goal        | Generic operator to pre-decrementing (--x) a LongInt using incrementPositive and incrementNegative
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> &LongInt<T, R>::operator--() {
    if (!isNegative) {
        if (digits[0] == 0) {
            digits[0] = 1;
            isNegative = true;
        } else {
            incrementNegative();
        }
    } else {
        incrementPositive();
    }
    return *this;
}

/* ---------------------------
Name        | operator--
Parameter(s)| int
Return      | LongInt<T, R>
Goal        | Generic operator to post-decrementing (x--) a LongInt using operator-- and assigning the result to the lhs
--------------------------- */
template<std::unsigned_integral T, T R>
LongInt<T, R> &LongInt<T, R>::operator--(int) {
    return --(*this);
}

/* ---------------------------
Name        | incrementPositive
Parameter(s)| -
Return      | -
Goal        | Generic function to increment a positive LongInt
--------------------------- */
template<std::unsigned_integral T, T R>
void LongInt<T, R>::incrementPositive() {
    size_t i = digits.size() - 1;
    bool needInsert = true;
    while (true) {
        // If the digit is smaller than the radix - 1, increment it and break the loop
        if (digits[i] < radix - 1) {
            ++digits[i];
            needInsert = false;
            break;
        }
        digits[i] = 0;
        if (i == 0) break;
        --i;
    }
    if (needInsert) {
        digits.insert(digits.begin(), 1);
    }
}

/* ---------------------------
Name        | incrementNegative
Parameter(s)| -
Return      | -
Goal        | Generic function to increment a negative LongInt
--------------------------- */
template<std::unsigned_integral T, T R>
void LongInt<T, R>::incrementNegative() {
    size_t i = digits.size() - 1;
    if (digits[i] == 0) {
        for (size_t j = i; j >= 0; --j) {
            // If the digit is 0, set it to 9 for the next iteration
            if (digits[j] == 0) {
                digits[j] = 9;
            } else {
                --digits[j];
                if (j == 0 && digits[j] == 0) {
                    digits.erase(digits.begin());
                }
                break;
            }
        }
    } else {
        // If the digit is 1 and the size of the vector is 1, set positive
        if (digits[i] == 1 && digits.size() == 1) {
            isNegative = false;
        }
        --digits[i];
    }
}

/* ---------------------------
Name        | operator<<
Parameter(s)| std::ostream &os, const LongInt<T, R> &rhs
Return      | std::ostream
Goal        | Generic operator to print a LongInt with the sign regardless of the radix
--------------------------- */
template<std::unsigned_integral T, T R>
std::ostream &operator<<(std::ostream &os, const LongInt<T, R> &rhs) {
    std::ostringstream oss;
    int columnWidth = os.width();
    if (os.flags() & std::ios_base::internal && rhs.isNegative) {
        os << std::setw(0) << std::left << '-' << std::internal << std::setw(columnWidth - 1);
    }
    if (rhs.isNegative && !(os.flags() & std::ios_base::internal)) {
        oss << '-';
    }
    if (os.flags() & std::ios_base::showpos && !rhs.isNegative) {
        oss << '+';
    }

    // Skip first iteration to avoid leading zeros
    bool firstIteration = true;
    for (auto value: rhs.digits) {
        if (firstIteration) {
            firstIteration = false;
            oss << value;
            continue;
        }
        // If the number of digits of the radix is greater than the number of digits of the value, add zeros
        if (floor(log10(R)) != floor(log10(value)) + 1) {
            oss << std::setfill('0') << std::setw(floor(log10(R))) << value;
        } else {
            oss << value;
        }
    }

    os << oss.str();
    os.width(0);
    return os;
}

/* ---------------------------
Name        | operator>>
Parameter(s)| std::istream &is, LongInt<T, R> &rhs
Return      | std::istream
Goal        | Generic operator to read a LongInt with the sign regardless of the radix
--------------------------- */
template<std::unsigned_integral T, T R>
std::istream &operator>>(std::istream &is, LongInt<T, R> &li) {
    char ch;
    std::string input;
    bool numberStarted = false;
    li.digits.clear();
    li.isNegative = false;
    // Continue until find a non-space character
    while (is.get(ch) && isspace(ch)) {}
    if (ch == '+' || ch == '-') {
        if (ch == '-') {
            li.isNegative = true;
        }
        is.get(ch);
    }
    while (true) {
        if (ch == '0' && !numberStarted) {
            if (!is.get(ch)) break;
        } else if (isdigit(ch)) {
            numberStarted = true;
            // Add the digit to the string and get the next character
            input += ch;
            if (!is.get(ch)) break;
        } else {
            break;
        }
    }
    if (input.empty()) {
        is.setstate(std::ios::failbit);
    }
    // Convert the string to a LongInt with the same radix as li
    li = static_cast<LongInt<T, R>>(stoull(input));
    return is;
}
#endif //LONGINTIMPLEMENT_H
