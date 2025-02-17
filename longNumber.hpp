#include <iostream>
#include <vector>
#include <stdint.h>
#include <cmath>

using namespace std;

class longNumber
{
private:
    bool positive = true;
    vector<uint32_t> num;
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
    longNumber(const vector<bool>& binary);
    longNumber(const vector<bool>& binary, int exponent);
    ~longNumber();

    void longNumberPrint() const;

    bool operator==(const longNumber& that) const;
    bool operator!=(const longNumber& that) const;
    bool operator>(const longNumber& that) const;
    bool operator<(const longNumber& that) const;

    longNumber Abs() const;
    longNumber multiply_const(uint32_t k) const;
    longNumber operator-() const;
    longNumber operator+(const longNumber& that) const;
    longNumber operator-(const longNumber& that) const;
    longNumber operator*(const longNumber& that) const;
    longNumber operator/(const longNumber& that) const;

    vector<bool> toBinary() const;
};