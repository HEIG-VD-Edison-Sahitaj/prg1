#include "../test/a061084.h"
#include "../longInt.h"
#include <iostream>

using namespace std;

int main() {
    LongInt test = a061084<LongInt>(1000);
    cout << "Test_A061084>" << test << endl;
}