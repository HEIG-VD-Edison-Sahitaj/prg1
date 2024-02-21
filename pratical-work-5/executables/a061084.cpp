/* ---------------------------
Labo        |   PRG1-L5 - Part2 - LongInt
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   08.01.2024
Deadline    |   19.01.2024 (2359)
Goal        |   Main for the a061084 function
Note        |   -
Source      |   -
--------------------------- */
#include "../test/a061084.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    auto test = a061084<LongInt<unsigned long long, 1000>>(1000);
    cout << "Test_A061084>" << test << endl;
}