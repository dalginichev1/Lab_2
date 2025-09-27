#include <string>
#include <cstring>
#include <stdexcept>
#include "twelve.hpp"

Twelve::Twelve() : data(1, 0) {};

Twelve::Twelve(const size_t& n, unsigned char t): data(n, t) {};

Twelve::Twelve(const std::initializer_list<unsigned char>& t): data(t.size())
{
    size_t i = t.size() - 1;
    for (auto it = t.begin(); it != t.end(); ++it, --i)
    {
        data.set(i, *it);
    }
}

Twelve::Twelve(const std::string& s): data(1, 0)
{
    if (s.empty())
    {
        return;
    }
    
    size_t start = 0;
    while (start < s.length() && s[start] == '0')
    {
        ++start;
    }
    if (start == s.length())
    {
        return;
    }

    size_t strSize = s.length() - start;
    data.resize(strSize);

    for (size_t i = 0; i < strSize; ++i)
    {
        char c = s[i + start];
        unsigned char value;
        if (c >= '0' && c <= '9')
        {
            value = c - '0';
        }
        else if (c == 'A' || c == 'a')
        {
            value = 10;
        }
        else if (c == 'B' || c == 'b')
        {
            value = 11;
        }
        else
        {
            throw std::invalid_argument("Invalid character");
        }

        data.set(strSize - i - 1, value);
    }
}

Twelve::Twelve(const Twelve& other): data(other.data) {}

Twelve::Twelve(Twelve&& other) noexcept: data(std::move(other.data)) {}

Twelve::~Twelve() noexcept {}

size_t Twelve::getSize(const Twelve& num) 
{
    return num.data.size();
}

bool Twelve::isZero(const Twelve& num)
{
    return num.data.size() == 1 && num.data.get(0) == 0;
}

int Twelve::compareAbsolute(const Twelve& a, const Twelve& b)
{
    if (a.data.size() > b.data.size()) return 1;
    if (a.data.size() < b.data.size()) return -1;

    for (int i = a.data.size() - 1; i >= 0; --i)
    {
        if (a.data.get(i) > b.data.get(i)) return 1;
        if (a.data.get(i) < b.data.get(i)) return -1;
    }

    return 0;
} 

Twelve Twelve::copy(const Twelve& num) 
{
    return Twelve(num);
}

Twelve Twelve::add(const Twelve& a, const Twelve& b)
{
    size_t maxSize = std::max(a.data.size(), b.data.size());
    Twelve result(maxSize + 1, 0);

    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.data.size()) ? a.data.get(i) : 0;
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;

        int sum  = digit_a + digit_b + carry;
        result.data.set(i, sum % 12);
        carry = sum / 12;
    }

    if (carry > 0)
    {
        result.data.set(maxSize, carry);
    }
    else
    {
        size_t newSize = maxSize;

        while (newSize > 1 && result.data.get(newSize - 1) == 0)
        {
            --newSize;
        }
        result.data.resize(newSize);
    }

    return result;
}

Twelve Twelve::substract(const Twelve& a, const Twelve& b)
{
    int cmp = compareAbsolute(a, b);

    if (cmp < 0)
    {
        throw std::invalid_argument("Negative number in substraction result");
    }
    if (cmp == 0)
    {
        return Twelve(1, 0);
    }

    size_t maxSize = a.data.size();
    Twelve result(maxSize, 0);

    int borrow = 0;

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = a.data.get(i);
        int digit_b = (i < b.data.size()) ? b.data.get(i) : 0;

        int diff = digit_a - digit_b - borrow;

        if (diff < 0)
        {
            diff += 12;
            borrow = 1;
        }

        else
        {
            borrow = 0;
        }

        result.data.set(i, diff);
    }

    size_t newSize = maxSize;
    while(newSize > 1 && result.data.get(newSize - 1) == 0)
    {
        --newSize;
    }

    result.data.resize(newSize);

    return result;
}

/*
Array Array::multByDigit(unsigned char digit) const
{
    if (digit == 0)
    {
        return Array(1, 0);
    }

    Array result(size + 1, 0);
    int carry = 0;

    for (size_t i = 0; i < size; ++i)
    {
        int prod = data[i] * digit + carry;
        result.data[i] = prod % 12;
        carry = prod / 12;
    }

    if (carry > 0)
    {
        result.data[size] = carry;
    }
    else
    {
        Array trimmed(result.size - 1, 0);
        std::memcpy(trimmed.data, result.data, (result.size) * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Array Array::shiftLeft(size_t position) const
{
    if ((size == 0 && data[0] == 0) || position == 0)
    {
        return *this;
    }

    Array result(size + position, 0);
    std::memcpy(result.data + position, data, size * sizeof(unsigned char));
    return result;
}

Array Array::mult(const Array& a, const Array& b)
{
    if (a.isZero || b.isZero)
    {
        return Array(1, 0);
    }

    Array result(1, 0);

    for (size_t i = 0; i < b.size; ++i)
    {
        Array temp = a.multByDigit(b.data[i]);
        Array shift = temp.shiftLeft(i);
        result = add(result, shilft);
    }

    return result;
}

Array Array::substractForDivision(const Array& a, const Array& b)
{
    Array result(a.size, 0);
    int borrow = 0;

    for (size_t i = 0; i < a.size; ++i)
    {
        int digit_a = a.data[i];
        int digit_b = (i < b.size) ? b.data[i] : 0;
        int diff = digit_a - digit_b - borrow;

        if (diff < 0)
        {
            diff += 12;
            borrow = 1;
        }
        
        else
        {
            borrow = 0;
        }

        result.data[i] = diff;
    }

    size_t realSize = result.size;
    while(realSize > 1 && result.data[realSize - 1] == 0)
    {
        --realSize;
    }

    if (realSize != result.size)
    {
        Array trimmed(realSize, 0);
        std::memcpy(trimmed.data, result.data, realSize * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Array Array::div(const Array& a, const Array& b)
{
    if (b.isZero())
    {
        throw std::invalid_argument("Divison by zero");
    }

    if (a.isZero())
    {
        return Array(1, 0);
    }

    int cmp = compareAbsolute(a, b);
    if (cmp < 0)
    {
        return Array(1, 0);
    }

    if (cmp == 0)
    {
        return Array(1, 1);
    }

    Array dividend = a;

    size_t maxDivSize = a.size - b.size + 1;
    Array div(maxDivSize, 0);

    for (int i = maxDivSize - 1; i >= 0; --i)
    {
        Array shiftDiv = b.shiftLeft(i);

        unsigned char digit = 0;
        while (compareAbsolute(dividend, shiftDiv) >= 0)
        {
            ++digit;
            dividend = substractForDivision(dividend, shiftDiv);
        }

        div.data[i] = digit;
        
        size_t realDivSize = div.size;
        while(realDivSize > 1 && div.data[realDivSize - 1] == 0)
        {
            --realDivSize;
        }

        if (realDivSize != div.size)
        {
            Array trimmed(realDivSize, 0);
            std::memcpy(trimmed.data, div.data, realDivSize * size(unsigned char));
            return trimmed;
        }

        return div;
    }
}

*/

bool Twelve::equals(const Twelve& a, const Twelve& b) 
{
    if (a.data.size() != b.data.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.data.size(); ++i)
    {
        if (a.data.get(i) != b.data.get(i))
        {
            return false;
        }
    }

    return true;
}

bool Twelve::lessThan(const Twelve& a, const Twelve& b) 
{
    if (a.data.size() > b.data.size())
    {
        return false;
    }

    if (a.data.size() < b.data.size())
    {
        return true;
    }

    for (int i = a.data.size() - 1; i >= 0; --i)
    {
        if (a.data.get(i) > b.data.get(i))
        {
            return false;
        }
        else if (a.data.get(i) < b.data.get(i))
        {
            return true;
        }
    }

    return false;
}

bool Twelve::greaterThan(const Twelve& a, const Twelve& b) 
{
    return lessThan(b, a);
}

std::string Twelve::toString(const Twelve& num)
{
    if (num.data.empty() || (num.data.size() == 1 && num.data.get(0) == 0))
    {
        return "0";
    }

    std::string result;

    for (int i = num.data.size() - 1; i >= 0; --i)
    {
        unsigned char digit = num.data.get(i);
        if (digit < 10)
        {
            result += ('0' + digit);
        }
        else
        {
            result += ('A' + (digit - 10));
        }
    }

    return result;
}

