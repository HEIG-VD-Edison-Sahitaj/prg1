#include "longInt.h"
#include <sstream>
#include <iostream>
#include "iomanip"

using namespace std;

LongInt emptyLongInt() {
    LongInt result = LongInt(0);
    result.digits.clear();
    return result;
}

bool isZero(LongInt &li) {
    bool result = true;
    for (auto value: li.digits) {
        if (value != 0) {
            return false;
        }
    }
    return result;
}

LongInt absValue(LongInt &li) {
    LongInt result = li;
    result.isNegative = false;
    return result;
}

LongInt addValues(LongInt &lhs, LongInt &rhs, bool isNegative) {
    LongInt result = emptyLongInt();
    const auto &longer = lhs.digits.size() >= rhs.digits.size() ? lhs.digits : rhs.digits;

    int carry = 0;
    for (size_t i = 0; i < longer.size(); ++i) {
        int digit = carry;
        if (i < lhs.digits.size()) {
            digit += lhs.digits[lhs.digits.size() - 1 - i];
        }
        if (i < rhs.digits.size()) {
            digit += rhs.digits[rhs.digits.size() - 1 - i];
        }
        result.digits.insert(result.digits.begin(), digit % LongInt::radix);
        carry = digit / LongInt::radix;
    }

    if (carry) {
        result.digits.insert(result.digits.begin(), carry);
    }
    result.isNegative = isNegative;
    if (isZero(result)) {
        return LongInt(0);
    }
    return result;
}

LongInt subValues(LongInt &lhs, LongInt &rhs, bool isNegative) {
    LongInt result = emptyLongInt();
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
            digit += LongInt::radix;
            carry = -1;
        } else {
            carry = 0;
        }
        result.digits.insert(result.digits.begin(), digit);
    }

    if (carry) {
        result.digits.insert(result.digits.begin(), carry);
    }

    while (!result.digits.empty() && result.digits[0] == 0) {
        result.digits.erase(result.digits.begin());
    }

    result.isNegative = isNegative;
    if (isZero(result)) {
        return LongInt(0);
    }
    return result;
}

LongInt multiplyValues(LongInt &lhs, LongInt &rhs, bool isNegative) {
    LongInt result = emptyLongInt();
    for (size_t i = 0; i < rhs.digits.size(); ++i) {
        LongInt temp = emptyLongInt();
        int carry = 0;
        for (size_t j = 0; j < lhs.digits.size(); ++j) {
            int digit = rhs.digits[rhs.digits.size() - 1 - i] * lhs.digits[lhs.digits.size() - 1 - j] + carry;
            temp.digits.insert(temp.digits.begin(), digit % LongInt::radix);
            carry = digit / LongInt::radix;
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
        return LongInt(0);
    }
    return result;
}

bool LongInt::operator==(const LongInt &rhs) const {
    return digits == rhs.digits &&
           isNegative == rhs.isNegative;
}

bool LongInt::operator!=(const LongInt &rhs) const {
    return !(rhs == *this);
}

bool LongInt::operator<(const LongInt &rhs) const {
    if (isNegative && !rhs.isNegative) {
        return true;
    } else if (!isNegative && rhs.isNegative) {
        return false;
    } else if (isNegative && rhs.isNegative) {
        if (digits.size() > rhs.digits.size()) {
            return true;
        } else if (digits.size() < rhs.digits.size()) {
            return false;
        } else {
            for (int i = 0; i < digits.size(); ++i) {
                if (digits[i] > rhs.digits[i]) {
                    return true;
                } else if (digits[i] < rhs.digits[i]) {
                    return false;
                }
            }
            return false;
        }
    } else {
        if (digits.size() < rhs.digits.size()) {
            return true;
        } else if (digits.size() > rhs.digits.size()) {
            return false;
        } else {
            for (int i = 0; i < digits.size(); ++i) {
                if (digits[i] < rhs.digits[i]) {
                    return true;
                } else if (digits[i] > rhs.digits[i]) {
                    return false;
                }
            }
            return false;
        }
    }
}

bool LongInt::operator>(const LongInt &rhs) const {
    return rhs < *this;
}

bool LongInt::operator<=(const LongInt &rhs) const {
    return !(rhs < *this) || rhs == *this;
}

bool LongInt::operator>=(const LongInt &rhs) const {
    return !(*this < rhs) || rhs == *this;
}

LongInt operator+(LongInt &lhs, LongInt &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, false);
        } else {
            return subValues(lhs, rhs, true);
        }
    } else if (!lhs.isNegative && rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, true);
        } else {
            return subValues(lhs, rhs, false);
        }
    } else if (lhs.isNegative && rhs.isNegative) {
        return addValues(lhs, rhs, true);
    } else {
        return addValues(lhs, rhs, false);
    }
}

LongInt operator+=(LongInt &lhs, LongInt &rhs) {
    lhs = lhs + rhs;
    return lhs;
}

LongInt operator-(LongInt &lhs, LongInt &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        return addValues(lhs, rhs, true);
    } else if (!lhs.isNegative && rhs.isNegative) {
        return addValues(lhs, rhs, false);
    } else if (lhs.isNegative && rhs.isNegative) {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, false);
        } else {
            return subValues(lhs, rhs, true);
        }
    } else {
        if (absValue(lhs) < absValue(rhs)) {
            return subValues(rhs, lhs, true);
        } else {
            return subValues(lhs, rhs, false);
        }
    }
}

LongInt operator-=(LongInt &lhs, LongInt &rhs) {
    lhs = lhs - rhs;
    return lhs;
}

LongInt operator*(LongInt &lhs, LongInt &rhs) {
    if (lhs.isNegative && !rhs.isNegative) {
        return multiplyValues(lhs, rhs, true);
    } else if (!lhs.isNegative && rhs.isNegative) {
        return multiplyValues(lhs, rhs, true);
    } else if (lhs.isNegative && rhs.isNegative) {
        return multiplyValues(lhs, rhs, false);
    } else {
        return multiplyValues(lhs, rhs, false);
    }
}

LongInt operator*=(LongInt &lhs, LongInt &rhs) {
    lhs = lhs * rhs;
    return lhs;
}

LongInt &LongInt::operator++() {
    if (!isNegative) {
        incrementPositive();
    } else {
        incrementNegative();
    }
    return *this;
}

LongInt &LongInt::operator++(int) {
    return ++(*this);
}

LongInt &LongInt::operator--() {
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

LongInt &LongInt::operator--(int){
    return --(*this);
}

void LongInt::incrementPositive() {
    size_t i = digits.size() - 1;
    bool needInsert = true;
    while (true) {
        if (digits[i] < radix - 1) {
            ++digits[i];
            needInsert = false;
            break;
        } else {
            digits[i] = 0;
            if (i == 0) break;
            --i;
        }
    }
    if (needInsert) {
        digits.insert(digits.begin(), 1);
    }
}

void LongInt::incrementNegative() {
    size_t i = digits.size() - 1;
    if (digits[i] == 0) {
        for (size_t j = i; j >= 0; --j) {
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
        if (digits[i] == 1 && digits.size() == 1) {
            isNegative = false;
        }
        --digits[i];
    }
}


ostream &operator<<(ostream &os, const LongInt &rhs) {
    ostringstream oss;
    int columnWidth = os.width();
    if (os.flags() & ios_base::internal && rhs.isNegative) {
        os << setw(0) << left << '-' << internal << setw(columnWidth - 1);
    }
    if (rhs.isNegative && !(os.flags() & ios_base::internal)) {
        oss << '-';
    }
    if (os.flags() & ios_base::showpos && !rhs.isNegative) {
        oss << '+';
    }
    for (auto value: rhs.digits) {
        oss << value;
    }
    os << oss.str();
    os.width(0);
    return os;
}

istream &operator>>(istream &is, LongInt &li) {
    char ch;
    string input = "";
    bool numberStarted = false;
    li.digits.clear();
    li.isNegative = false;
    while (is.get(ch) && isspace(ch)) {}// Continue until find a non-space character
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
            input += ch;
            if (!is.get(ch)) break;
        } else {
            break;
        }
    }
    if (input.empty()) {
        is.setstate(ios::failbit);
    } else {
        for (size_t i = 0; i < input.length(); i++) {
            li.digits.push_back(input[i] - '0');
        }
    }
    return is;
}