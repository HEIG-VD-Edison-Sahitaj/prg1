//
// Created by Shadow on 15/12/2023.
//

#include "test/fibonacci.h"
#include "test/a061084.h"
#include "test/factorial.h"
#include "longInt.h"
#include <iostream>

using namespace std;

int main() {
    int lla = -4603;
    LongInt a(lla);
    cout << static_cast<int>(a) << endl;
}