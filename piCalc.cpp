#include <iostream>
#include <chrono>
#include "longNumber.hpp"

using namespace std::chrono;

longNumber arctan(longNumber x, int accuracy)
{
    longNumber epsilon = (1.0_longnum).byte_move(-accuracy - 1);
    longNumber ans = 0, divizior(1), delta(2), prod = x * x, curr(1), x_pow = x;
    int i = 0;
    while (curr > epsilon)
    {
        curr = x_pow / divizior;
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
        i += 1;
    }
    return ans;
}


int main()
{
    int decimal_accuracy;
    scanf("%d", &decimal_accuracy);
    if (decimal_accuracy < 0) return 1;
    double scale = decimal_accuracy * log2(10) / 32;
    int binary_accuracy =  static_cast<int>(floorf64(scale)) + 1;

    auto start = high_resolution_clock::now();

    longNumber one(1), five(5), n239(239);
    one = one.extendZeros(binary_accuracy);
    five = five.extendZeros(binary_accuracy); 
    n239 = n239.extendZeros(binary_accuracy);
    longNumber x1 = one / five, x2 = one / n239;
    longNumber pi = 4.0_longnum * arctan(x1, binary_accuracy) - arctan(x2, binary_accuracy);
    pi = pi.multiply_const(4U);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    double t = ((double) duration.count()) / 1000000;
    printf("Calculation time: %lf\n", t);

    std::string result = pi.toDecimal();
    for (int i = 0; i < decimal_accuracy + 2; i++)
    {
        printf("%c", result[i]);
    }
    printf("\n");

    return 0;
}