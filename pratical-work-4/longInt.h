#ifndef PRG1_LABO4_LONGINT_SAD_LONGINT_H
#define PRG1_LABO4_LONGINT_SAD_LONGINT_H
#include <vector>
#include <cmath>
#include <iosfwd>

class LongInt {
public:
    using digitT = unsigned int;
    static const LongInt::digitT radix = 10;
    template<typename T>
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

    explicit operator int() const {
        int result = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            result = isNegative ? result - digits[i] * pow(radix, digits.size() - i - 1) : result + digits[i] * pow(radix, digits.size() - i - 1);
        }
        return result;
    }
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
    friend LongInt operator+(LongInt &lhs, LongInt &rhs);
    friend LongInt operator+=(LongInt &lhs, LongInt &rhs);
    friend LongInt operator-(LongInt &lhs, LongInt &rhs);
    friend LongInt operator-=(LongInt &lhs, LongInt &rhs);
    friend LongInt operator*(LongInt &lhs, LongInt &rhs);
    friend LongInt operator*=(LongInt &lhs, LongInt &rhs);
    LongInt & operator++();
    LongInt & operator++(int);
    LongInt & operator--();
    LongInt & operator--(int);
    friend std::ostream& operator<<(std::ostream &os, const LongInt &rhs);
    friend std::istream& operator>>(std::istream& is, LongInt& li);
private:
    std::vector<LongInt::digitT> digits;
    bool isNegative = true;
    friend LongInt emptyLongInt();
    friend bool isZero(LongInt &li);
    friend LongInt absValue(LongInt &li);
    friend LongInt addValues(LongInt &lhs, LongInt &rhs, bool isNegative);
    friend LongInt subValues(LongInt &lhs, LongInt &rhs, bool isNegative);
    friend LongInt multiplyValues(LongInt &lhs, LongInt &rhs, bool isNegative);
    void incrementPositive();
    void incrementNegative();
};

#endif //PRG1_LABO4_LONGINT_SAD_LONGINT_H
