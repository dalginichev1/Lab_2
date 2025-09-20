#include <string>
#include <cstring>
#include <stdexcept>
#include "twelve.hpp"

Twelve::Twelve() : size(0), data(new unsigned char) {};

Twelve::Twelve(const size_t& n, unsigned char t): size(n), data(new unsigned char[n])
{
    std::fill(data, data + n, t);
}

Twelve::Twelve(const std::initializer_list<unsigned char>& t): size(t.size()), data(new unsigned char[t.size()])
{
    std::copy(t.begin(), t.end(), data);
}

Twelve::Twelve(const std::string& s)
{
    if (s.empty())
    {
        size = 0;
        data = nullptr;
        return;
    }

    size = s.length();
    data = new unsigned char[size];

    for (size_t i = 0; i < size; ++i)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            data[size - i - 1] = c - '0';
        }

        else if (c == 'A' || c == 'B')
        {
            data[size - i - 1] = 10 + (c - 'A');
        }

        else
        {
            throw std::invalid_argument("Invalid character");
        }
    }
}

Twelve::Twelve(const Twelve& other): size(other.size), data(new unsigned char[other.size])
{
    std::memcpy(data, other.data, size * sizeof(unsigned char));
}

Twelve::Twelve(Twelve&& other) noexcept: size(other.size), data(other.data)
{
    other.size = 0;
    other.data = nullptr;
}

Twelve::~Twelve() noexcept
{
    delete[] data;
}

size_t Twelve::getSize() const
{
    return size;
}

bool Twelve::isZero() const
{
    return size == 1 && data[0] == 0;
}

int Twelve::compareAbsolute(const Twelve& a, const Twelve& b)
{
    if (a.size > b.size) return 1;
    if (a.size < b.size) return -1;

    for (int i = a.size - 1; i >= 0; --i)
    {
        if (a.data[i] > b.data[i]) return 1;
        if (a.data[i] < b.data[i]) return -1;
    }

    return 0;
}

Twelve Twelve::copy() const
{
    Twelve result(size, 0);
    std::memcpy(result.data, data, size * sizeof(unsigned char));
    return result;
}

Twelve Twelve::add(const Twelve& a, const Twelve& b)
{
    size_t maxSize = 0;

    if (a.size >= b.size)
    {
        maxSize = a.size;
    }

    else
    {
        maxSize = b.size;
    }

    Twelve result(maxSize + 1, 0);

    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a.size) ? a.data[i] : 0;
        int digit_b = (i < b.size) ? b.data[i] : 0;

        int sum  = digit_a + digit_b + carry;
        result.data[i] = sum % 12;
        carry = sum / 12;
    }
    if (carry > 0)
    {
        result.data[maxSize] = carry;
    }

    else
    {
        Twelve trimmed(maxSize, 0);
        std::memcpy(trimmed.data, result.data, maxSize * sizeof(unsigned char));
        return trimmed;
    }

    size_t newSize = result.size;
    while (newSize > 1 && result.data[newSize - 1] == 0)
    {
        --newSize;
    }

    if (newSize != result.size)
    {
        Twelve trimmed(newSize, 0);
        std::memcpy(trimmed.data, result.data, newSize * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Twelve Twelve::substract(const Twelve& a, const Twelve& b)
{
    bool isNegative = false;
    const Twelve* bigger = &a;
    const Twelve* smaller = &b;

    int cmp = compareAbsolute(a, b);
    if (cmp > 0)
    {
        bigger = &a;
        smaller = &b;
    }
    else if (cmp < 0)
    {
        throw std::invalid_argument("Negative number in substraction result");
    }
    else
    {
        return Twelve(1, 0);
    }

    size_t maxSize = bigger->size;
    Twelve result(maxSize, 0);

    int borrow = 0;

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_bigger = bigger->data[i];
        int digit_smaller = (i < smaller->size) ? smaller->data[i] : 0;

        int diff = digit_bigger - digit_smaller - borrow;

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

    size_t newSize = maxSize;
    while(newSize > 1 && result.data[newSize - 1] == 0)
    {
        --newSize;
    }

    if (newSize != maxSize)
    {
        Twelve trimmed(newSize, 0);
        std::memcpy(trimmed.data, result.data, newSize *sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

/*
Twelve Twelve::multByDigit(unsigned char digit) const
{
    if (digit == 0)
    {
        return Twelve(1, 0);
    }

    Twelve result(size + 1, 0);
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
        Twelve trimmed(result.size - 1, 0);
        std::memcpy(trimmed.data, result.data, (result.size) * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Twelve Twelve::shiftLeft(size_t position) const
{
    if ((size == 0 && data[0] == 0) || position == 0)
    {
        return *this;
    }

    Twelve result(size + position, 0);
    std::memcpy(result.data + position, data, size * sizeof(unsigned char));
    return result;
}

Twelve Twelve::mult(const Twelve& a, const Twelve& b)
{
    if (a.isZero || b.isZero)
    {
        return Twelve(1, 0);
    }

    Twelve result(1, 0);

    for (size_t i = 0; i < b.size; ++i)
    {
        Twelve temp = a.multByDigit(b.data[i]);
        Twelve shift = temp.shiftLeft(i);
        result = add(result, shilft);
    }

    return result;
}

Twelve Twelve::substractForDivision(const Twelve& a, const Twelve& b)
{
    Twelve result(a.size, 0);
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
        Twelve trimmed(realSize, 0);
        std::memcpy(trimmed.data, result.data, realSize * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Twelve Twelve::div(const Twelve& a, const Twelve& b)
{
    if (b.isZero())
    {
        throw std::invalid_argument("Divison by zero");
    }

    if (a.isZero())
    {
        return Twelve(1, 0);
    }

    int cmp = compareAbsolute(a, b);
    if (cmp < 0)
    {
        return Twelve(1, 0);
    }

    if (cmp == 0)
    {
        return Twelve(1, 1);
    }

    Twelve dividend = a;

    size_t maxDivSize = a.size - b.size + 1;
    Twelve div(maxDivSize, 0);

    for (int i = maxDivSize - 1; i >= 0; --i)
    {
        Twelve shiftDiv = b.shiftLeft(i);

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
            Twelve trimmed(realDivSize, 0);
            std::memcpy(trimmed.data, div.data, realDivSize * size(unsigned char));
            return trimmed;
        }

        return div;
    }
}

*/

Twelve Twelve::add(const Twelve& other) const
{
    return add(*this, other);
}

Twelve Twelve::substract(const Twelve& other) const
{
    return substract(*this, other);
}

/*
Twelve Twelve::mult(const Twelve& other) const
{
    return mult(*this, other);
}

Twelve Twelve::divide(const Twelve& other) const
{
    return divide(*this, other);
}
*/

bool Twelve::equals(const Twelve& other) const
{
    if (size != other.size)
    {
        return false;
    }

    for(size_t i = 0; i < size; ++i)
    {
        if (data[i] != other.data[i])
        {
            return false;
        }
    }

    return true;
}

bool Twelve::lessThan(const Twelve& other) const
{
    if (size < other.size)
    {
        return true;
    }

    if (size > other.size)
    {
        return false;
    }

    for (int i = size - 1; i >= 0; --i)
    {
        if (data[i] < other.data[i])
        {
            return true;
        }

        if (data[i] > other.data[i])
        {
            return false;
        }
    }

    return false;
}

bool Twelve::greaterThan(const Twelve& other) const
{
    return other.lessThan(*this);
}

std::string Twelve::toString() const
{
    if (size == 0) return "0";

    std::string result;

    for (int i = size - 1; i >= 0; --i)
    {
        unsigned char digit = data[i];
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

