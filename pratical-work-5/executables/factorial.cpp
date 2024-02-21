/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Main for the factorial function
Note        |   -
Source      |   -
--------------------------- */
#include "../test/factorial.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    auto test = factorial<LongInt<unsigned long long, 10>>(100);
    cout << "Test_Factorial>" << test << endl;
}