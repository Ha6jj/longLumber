#ifndef LONGNUMBER_HEADER_GUARD
#define LONGNUMBER_HEADER_GUARD

#include <iostream>
#include <vector>
#include <stdint.h>
#include <cmath>

class longNumber
{
private:
    bool positive = true;
    std::vector<uint32_t> num;
    int exp = 0;

    void verify_zeros();
    bool greater_positive(const longNumber& that) const;
    longNumber add_positive(const longNumber& that) const;
    longNumber substract_positive(const longNumber& that) const;
    longNumber byte_move(int bytes) const;
    longNumber multiply_positive(const longNumber& that) const;
    longNumber divide_positive_zero_exp(const longNumber& that) const;
    longNumber divide_positive(const longNumber& that) const;
public:
    longNumber(void);
    longNumber(int a);
    longNumber(double a);
    longNumber(const longNumber& that);
    longNumber(const std::vector<bool>& binary);
    longNumber(const std::vector<bool>& binary, int exponent);
    ~longNumber();

    void longNumberPrint() const;

    bool operator==(const longNumber& that) const;
    bool operator!=(const longNumber& that) const;
    bool operator>(const longNumber& that) const;
    bool operator<(const longNumber& that) const;

    friend longNumber operator""_longnum(long double number);
    longNumber& operator=(const longNumber& that) = default;

    longNumber Abs() const;
    longNumber truncate() const;
    longNumber multiply_const(uint32_t k) const;
    longNumber operator-() const;
    longNumber operator+(const longNumber& that) const;
    longNumber operator-(const longNumber& that) const;
    longNumber operator*(const longNumber& that) const;
    longNumber operator/(const longNumber& that) const;

    std::vector<bool> toBinary() const;
    std::string toDecimal() const;
};

longNumber operator""_longnum(long double number);

#endif