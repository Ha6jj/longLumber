#include <iostream>
#include "longNumber.hpp"

using namespace std;

int main()
{
    double c1 = -9.6, c2 = 15.289;
    longNumber a(-1), b(2), c(c1), d(c2), one(1), zero(0);
    longNumber tmp = c * d;
    tmp.longNumberPrint(); // -146.77439999999999
    (one + a).longNumberPrint(); // 0
    (-one + one).longNumberPrint(); // 0
    (tmp / d).longNumberPrint(); // -9.6
    (tmp / c).longNumberPrint(); // 15.289
    (zero / tmp).longNumberPrint(); // 0

    return 0;
}