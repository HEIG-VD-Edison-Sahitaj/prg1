#include "../test/fibonacci.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    LongInt test = fibonacci<LongInt>(1000);
    cout << "Test_Fibonacci>" << test << endl;
}