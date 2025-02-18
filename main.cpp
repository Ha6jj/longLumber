#include <iostream>
#include "longNumber.hpp"

using namespace std;

int main()
{
    double c1 = -9.6, c2 = 15.289;
    longNumber a(-1), b(2), c(c1), d(c2), one(1), zero(0);
    longNumber tmp;
    longNumber r = a * (tmp = c * d);
    r.longNumberPrint();
    tmp.longNumberPrint(); // -146.77439999999999
    (one + a).longNumberPrint(); // 0
    (-one + one).longNumberPrint(); // 0
    (tmp / d).longNumberPrint(); // -9.6
    (tmp / c).longNumberPrint(); // 15.289
    (zero / tmp).longNumberPrint(); // 0
    (a / zero).longNumberPrint(); // error

    longNumber smth = 2.5_longnum;
    (one + smth).longNumberPrint();
    return 0;
}