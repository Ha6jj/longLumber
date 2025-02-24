#include <iostream>
#include "longNumber.hpp"


void test_constructor()
{
    bool result = true;

    result = result && (-123.0_longnum == longNumber(-123.0));
    result = result && (longNumber(0.0) != longNumber(0));
    result = result && (longNumber(0) != longNumber());
    result = result && (longNumber(-12345) == longNumber(-12345.00));

    if (result)
        std::cout << "[OK]    Constructors are ok\n";
    else
        std::cout << "[FAIL] Constructors are not ok\n";
}

void test_comparison()
{
    bool result = true;

    longNumber a(1), b(-1), c(1.5), d(0);
    result = result && (a > b);
    result = result && (a == -b);
    result = result && (a < c);
    result = result && (c != d);

    if (result)
        std::cout << "[OK]    Comparison is ok\n";
    else
        std::cout << "[FAIL] Comparison is not ok\n";
}

void test_arithmetic()
{
    bool result = true;

    longNumber a(1), b(-1), c(1.5), d(0), e(123.45);
    result = result && (a * e == e);
    result = result && (a + b == d);
    result = result && (c - b == a + c);
    result = result && (e / b == -e);
    result = result && (d.multiply_const(777) == d);

    if (result)
        std::cout << "[OK]    Arithmetic is ok\n";
    else
        std::cout << "[FAIL] Arithmetic is not ok\n";
}

void test_utils()
{
    bool result = true;

    longNumber a(1), b(-1), c(1.5), d(0), e(123.1);
    result = result && ((-e).Abs() == e);
    result = result && (c.truncate() == a);
    result = result && ((c * (a + a)).extendZeros(-1) == longNumber(3));

    if (result)
        std::cout << "[OK]    Utils are ok\n";
    else
        std::cout << "[FAIL] Utils are not ok\n";
}


int main()
{
    test_constructor();
    test_comparison();
    test_arithmetic();
    test_utils();
    return 0;
}