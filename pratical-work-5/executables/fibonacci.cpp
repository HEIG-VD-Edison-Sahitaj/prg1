/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Main for the fibonacci function
Note        |   -
Source      |   -
--------------------------- */
#include "../test/fibonacci.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    auto test = fibonacci<LongInt<unsigned long long, 100>>(1000);
    cout << "Test_Fibonacci>" << test << endl;
}