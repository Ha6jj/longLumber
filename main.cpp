#include <iostream>
#include "longNumber.hpp"

longNumber arctan(longNumber x)
{
    int n = 50;
    longNumber ans = 0, divizior(1), delta(2), prod = x * x, curr, x_pow = x;
    for (int i = 0; i < n; ++i)
    {
        // printf("%d x_pow: \n", i + 1);
        // x_pow.longNumberPrint();

        // printf("%d divizior: \n", i + 1);
        // divizior.longNumberPrint();

        curr = x_pow / divizior;
        // printf("%d curr: \n", i + 1);
        // curr.longNumberPrint();

        if (i % 2 == 0)
        {
            ans = ans + curr;
        }
        else
        {
            ans = ans - curr;
        }
        x_pow = x_pow * prod;
        divizior = divizior + delta;
    }
    return ans;
}


int main()
{
    longNumber x1 = 1.0_longnum / 5.0_longnum, x2 = 1.0_longnum / 239.0_longnum;
    longNumber pi = 4.0_longnum * arctan(x1) - arctan(x2);
    pi = pi.multiply_const(4U);
    std::cout << pi.toDecimal() << std::endl;

    return 0;
}