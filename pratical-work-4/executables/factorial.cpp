#include "../test/factorial.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    LongInt test = factorial<LongInt>(100);
    cout << "Test_Factorial>" << test << endl;
}