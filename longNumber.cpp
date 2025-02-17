#include "longNumber.hpp"

#define MAX_ACCURACY 10

longNumber::longNumber()
{

}

longNumber::longNumber(int a)
{
    //printf("Making new obj from int\n");
    this->positive = a >= 0;
    if (!this->positive)
    {
        if (a != INT32_MIN)
        {
            a = -a;
        }
        else printf("Failed to extrat sign\n");
    }
    this->num.push_back((uint32_t) a);
}

longNumber::longNumber(double a)
{
    //printf("Making new obj from double\n");
    this->positive = a >= 0;
    if (!this->positive)
    {
        a = -a;
    }
    double tmp, mod = ((double) 0xffffffff) + 1;
    double integer_part = floorf64(a);
    double fractional_part = a - integer_part;

    while (fractional_part > 0 && this->exp < MAX_ACCURACY)
    {
        fractional_part = fractional_part * mod;
        tmp = floorf64(fractional_part);
        this->num.push_back((uint32_t) tmp);
        this->exp += 1;
        fractional_part -= tmp;
    }
    int n = this->num.size();
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(this->num[i], this->num[n - i - 1]);
    }

    while (integer_part > 0)
    {
        tmp = floorf64(integer_part / mod);
        this->num.push_back((uint32_t) (integer_part - tmp * mod));
        integer_part = tmp;
    }
    this->verify_zeros();
}

longNumber::longNumber(const vector<bool>& binary)
{
    int len = binary.size(), k = (32 - len % 32) % 32;
    uint32_t digit = 0;
    for (int i = 0; i < len; i++)
    {
        digit *= 2;
        if (binary[i])
        {
            digit += 1;
        }
        k += 1;
        if (k >= 32)
        {
            k = 0;
            this->num.push_back(digit);
            digit = 0;
        }
    }
    if (digit) this->num.push_back(digit);

    int n = this->num.size();
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(this->num[i], this->num[n - i - 1]);
    }
    this->verify_zeros();
}

longNumber::longNumber(const vector<bool>& binary, int exponent)
{
    int len = binary.size(), k = (32 - len % 32) % 32;
    uint32_t digit = 0;
    for (int i = 0; i < len; i++)
    {
        digit *= 2;
        if (binary[i]) digit += 1;
        k += 1;
        if (k >= 32)
        {
            k = 0;
            this->num.push_back(digit);
            digit = 0;
        }
    }
    if (digit != 0)
    {
        for (int i = 0; i < (32 - exponent % 32) % 32; i++)
        {
            digit *= 2;
        }
        this->num.push_back(digit);
    }

    this->exp = exponent / 32;
    if (exponent % 32 != 0) this->exp += 1;

    int n = this->num.size();
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(this->num[i], this->num[n - i - 1]);
    }
    this->verify_zeros();
}

longNumber::longNumber(const longNumber& that)
{
    //printf("Making new obj copying another\n");
    this->exp = that.exp;
    this->positive = that.positive;
    this->num = that.num;
    this->verify_zeros();
}

longNumber::~longNumber()
{
    //printf("Deleting obj\n");
}

void longNumber::longNumberPrint() const
{
    if (!this->positive)
    {
        printf("-");
    }
    int n = this->num.size();
    for (int i = 0; i < n; i++)
    {
        if (n - i == this->exp)
        {
            printf(".");
        }
        printf("%u\'", this->num[n - i - 1]);
    }
    printf("\n");
}

void longNumber::verify_zeros()
{
    int n = this->num.size();
    if (n == 0) return;
    while (this->num[n - 1] == 0U && (n - this->exp > 1))
    {
        this->num.pop_back();
        n -= 1;
    }

    int ind = 0;
    while (ind < this->exp && this->num[ind] == 0)
    {
        ind += 1;
    }
    this->num.erase(this->num.begin(), this->num.begin() + ind);
    this->exp -= ind;

    longNumber negative_zero(0);
    negative_zero.positive = false;
    if (*this == negative_zero)
    {
        this->positive = true;
    }
    return;
}

longNumber longNumber::Abs() const
{
    longNumber result(*this);
    result.positive = true;
    return result;
}

bool longNumber::operator==(const longNumber& that) const
{
    if (this->exp != that.exp) return false;
    int len1 = this->num.size(), len2 = that.num.size();
    if (len1 != len2) return false;
    for (int i = 0; i < len1; i++)
    {
        if (this->num[i] != that.num[i]) return false;
    }
    return true;
}

bool longNumber::operator!=(const longNumber& that) const
{
    return !(*this == that);
}

bool longNumber::greater_positive(const longNumber& that) const
{
    // assert both positive
    if (*this == that)
    {
        return false;
    }

    int exp1 = this->exp,        exp2 = that.exp;
    int len1 = this->num.size(), len2 = that.num.size();
    if (len1 - exp1 > len2 - exp2)
    {
        return true;
    }
    else if (len1 - exp1 < len2 - exp2)
    {
        return false;
    }

    for (int i = 0; i < max(len1, len2); i++)
    {   
        if (i == min(len1, len2))
        {
            return (len1 > len2);
        }
        if (this->num[len1 - i - 1] > that.num[len2 - i - 1])
        {
            return true;
        }
        if (this->num[len1 - i - 1] < that.num[len2 - i - 1])
        {
            return false;
        }
    }
    return true;
}

bool longNumber::operator>(const longNumber& that) const
{
    if (this->positive)
    {
        if (that.positive)
        {
            return this->greater_positive(that);
        }
        else
        {
            return true;
        }
    }
    else
    {
        if (that.positive)
        {
            return false;
        }
        else
        {
            return !(*this == that || (-*this).greater_positive(-that));
        }
    }
}

bool longNumber::operator<(const longNumber& that) const
{
    return !(*this == that || *this > that);
}

longNumber longNumber::operator-() const
{
    longNumber result(*this);
    result.positive = !result.positive;
    result.verify_zeros();
    return result;
}

longNumber longNumber::add_positive(const longNumber& that) const
{
    longNumber result{};
    if (!(this->positive && that.positive)) return result;

    int exp1 = this->exp,        exp2 = that.exp;
    int len1 = this->num.size(), len2 = that.num.size();
    int ind1 = 0,                ind2 = 0;
    uint64_t tmp, mod = 1LL << 32, a = 0, b = 0;
    bool reminder = false;

    if (exp1 > exp2)
        for (ind1 = 0; ind1 < exp1 - exp2; ind1++)
            result.num.push_back(this->num[ind1]);
    else
        for (ind2 = 0; ind2 < exp2 - exp1; ind2++)
            result.num.push_back(that.num[ind2]);
    
    result.exp = max(exp1, exp2);

    while (ind1 < exp1 + max(len1 - exp1, len2 - exp2))
    {
        a = 0; b = 0;
        if (ind1 < len1)
        {
            a = this->num[ind1];
        }
        if (ind2 < len2)
        {
            b = that.num[ind2];
        }
        tmp = a + b + reminder;
        if (tmp >= mod)
        {
            reminder = true;
            tmp -= mod;
        }
        else
        {
            reminder = false;
        }
        result.num.push_back((uint32_t) tmp);
        ind1 += 1; ind2 += 1;
    }
    
    result.verify_zeros();
    return result;
}

longNumber longNumber::substract_positive(const longNumber& that) const
{
    longNumber result{};
    if (!(this->positive && that.positive)) return result;

    int exp1 = this->exp,        exp2 = that.exp;
    int len1 = this->num.size(), len2 = that.num.size();
    int ind1 = 0,                ind2 = 0;
    uint64_t tmp, mod = 1LL << 32, a = 0, b = 0;
    bool reminder = false;

    if (exp1 > exp2)
        for (ind1 = 0; ind1 < exp1 - exp2; ind1++)
            result.num.push_back(this->num[ind1]);
    else
        for (ind2 = 0; ind2 < exp2 - exp1; ind2++)
        {
            tmp = (mod - that.num[ind2]) - reminder;
            result.num.push_back(tmp);
            reminder = true;
        }
    
    result.exp = max(exp1, exp2);

    while (ind1 < exp1 + max(len1 - exp1, len2 - exp2))
    {
        a = 0; b = 0;
        if (ind1 < len1)
        {
            a = this->num[ind1];
        }
        if (ind2 < len2)
        {
            b = that.num[ind2];
        }
        tmp = (mod + a - b) - reminder;
        if (tmp >= mod)
        {
            reminder = false;
            tmp -= mod;
        }
        else
        {
            reminder = true;
        }
        result.num.push_back((uint32_t) tmp);
        ind1 += 1; ind2 += 1;
    }
    
    result.verify_zeros();
    return result;
}

longNumber longNumber::operator+(const longNumber& that) const
{
    if (this->positive && that.positive)
    {
        return this->add_positive(that);
    }
    if (!this->positive && !that.positive)
    {
        return -(this->add_positive(-that));
    }
    if (this->positive)
    {
        longNumber tmp = that.Abs();
        if (this->greater_positive(tmp))
        {
            return this->substract_positive(tmp);
        }
        else
        {
            return -(tmp.substract_positive(*this));
        }
    }
    if (that.positive)
    {
        longNumber tmp = this->Abs();
        if (tmp.greater_positive(that))
        {
            return -(tmp.substract_positive(that));
        }
        else
        {
            return that.substract_positive(tmp);
        }
    }
    return longNumber(0);
}

longNumber longNumber::operator-(const longNumber& that) const
{
    longNumber result = (*this) + (-that);
    return result;
}

longNumber longNumber::multiply_const(uint32_t k) const
{
    longNumber result{};
    uint64_t reminder = 0, tmp, mod = 1UL << 32;
    int n = this->num.size();
    for (int i = 0; i < n; i++)
    {
        tmp = ((uint64_t) this->num[i]) * k + reminder;
        result.num.push_back((uint32_t) tmp % mod);
        reminder = tmp / mod;
    }
    result.exp = this->exp;
    if (reminder != 0)
    {
        result.num.push_back(reminder);
    }
    result.verify_zeros();
    return result;
}

longNumber longNumber::byte_move(int bytes) const
{
    longNumber result;
    result.positive = this->positive;
    result.exp = max(0, this->exp - bytes);
    int n = this->num.size();
    for (int i = 0; i < bytes; i++)
    {
        result.num.push_back(0U);
    }
    for (int i = 0; i < n; i++)
    {
        result.num.push_back(this->num[i]);
    }
    while ((int) result.num.size() < result.exp + 1)
    {
        result.num.push_back(0U);
    }
    return result;
}

longNumber longNumber::multiply_positive(const longNumber& that) const
{
    longNumber result(0), tmp(0);
    // assert both positive
    int len1 = this->num.size();
    for (int i = 0; i < len1; i++)
    {
        tmp = that.multiply_const(this->num[i]);
        tmp = tmp.byte_move(i - this->exp);
        result = result + tmp;
    }
    result.verify_zeros();
    return result;
}

longNumber longNumber::operator*(const longNumber& that) const
{
    longNumber result = (this->Abs()).multiply_positive(that.Abs());
    if (this->positive != that.positive) return -result;
    return result;
}

vector<bool> longNumber::toBinary() const
{
    int len = this->num.size();
    vector<bool> result;
    uint32_t curr;
    for (int i = 0; i < len; i++)
    {
        curr = this->num[i];
        for (int j = 0; j < 32; j++)
        {
            result.push_back(curr % 2 == 1);
            curr /= 2;
        }
    }

    int n = result.size();
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(result[i], result[n - i - 1]);
    }
    return result;
}

longNumber longNumber::divide_positive_zero_exp(const longNumber& that) const
{
    vector<bool> dividend = this->toBinary();
    int n = dividend.size();

    vector<bool> buffer, result;
    longNumber operand(1), zero(0);
    int ind1 = 0, exponent = 0;
    while ((ind1 < n) || (operand != zero && (ind1 - n < MAX_ACCURACY * 32)))
    {
        if (ind1 < n)
        {
            buffer.push_back(dividend[ind1]);
        }
        else
        {
            buffer.push_back(false);
            exponent += 1;
        }

        operand = longNumber(buffer); // СЮДА НЕ СМОТРЕТЬ (ВСЕ МАКСИМАЛЬНО ОПТИМИЗИРОВАННО)!!!

        if (operand > that || operand == that)
        {
            result.push_back(true);
            operand = operand - that;
            buffer = operand.toBinary();
        }
        else
        {
            result.push_back(false);
        }
        ind1 += 1;
    }
    
    return longNumber(result, exponent);
}

longNumber longNumber::divide_positive(const longNumber& that) const
{
    // assert both positive

    longNumber first = this->byte_move(this->exp), 
               second = that.byte_move(that.exp);
    longNumber result = first.divide_positive_zero_exp(second);
    result = result.byte_move(that.exp - this->exp);
    result.verify_zeros();
    return result;
}

longNumber longNumber::operator/(const longNumber& that) const
{
    longNumber zero(0);
    if (that == zero)
    {
        printf("[ERROR] Division by zero!\n"); 
        return longNumber(0);
    }

    longNumber result = (this->Abs()).divide_positive(that.Abs());
    if (this->positive != that.positive) return -result;
    return result;
}