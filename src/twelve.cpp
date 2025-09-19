#include <string>
#include <cstring>
#include <stdexcept>
#include "twelve.hpp"

Array::Array() : size(0), data(new unsigned char) {};

Array::Array(const size_t& n, unsigned char t): size(n), data(new unsigned char[n])
{
    std::fill(data, data + n, t);
}

Array::Array(const std::initializer_list<unsigned char>& t): size(t.size()), data(new unsigned char[t.size()])
{
    std::copy(t.begin(), t.end(), data);
}

Array::Array(const std::string& s)
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

Array::Array(const Array& other): size(other.size), data(new unsigned char[other.size])
{
    std::memcpy(data, other.data, size * sizeof(unsigned char));
}

Array::Array(Array&& other) noexcept: size(other.size), data(other.data)
{
    other.size = 0;
    other.data = nullptr;
}

Array::~Array() noexcept
{
    delete[] data;
}

size_t Array::getSize() const
{
    return size;
}

bool Array::isZero() const
{
    return size == 1 && data[0] == 0;
}

Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        std::memcpy(data, other.data, size * sizeof(unsigned char));
    }

    return *this;
}
int Array::compareAbsolute(const Array& a, const Array& b)
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

Array Array::add(const Array& a, const Array& b)
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

    Array result(maxSize + 1, 0);

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
        Array trimmed(maxSize, 0);
        std::memcpy(trimmed.data, result.data, maxSize * sizeof(unsigned char));
        result = trimmed;
    }

    size_t newSize = result.size;
    while (newSize > 1 && result.data[newSize - 1] == 0)
    {
        --newSize;
    }

    if (newSize != result.size)
    {
        Array trimmed(newSize, 0);
        std::memcpy(trimmed.data, result.data, newSize * sizeof(unsigned char));
        return trimmed;
    }

    return result;
}

Array Array::substract(const Array& a, const Array& b)
{
    bool isNegative = false;
    const Array* bigger = &a;
    const Array* smaller = &b;

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
        return Array(1, 0);
    }

    size_t maxSize = bigger->size;
    Array result(maxSize, 0);

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
        Array trimmed(newSize, 0);
        std::memcpy(trimmed.data, result.data, newSize *sizeof(unsigned char));
        result = trimmed;
    }

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

Array Array::add(const Array& other) const
{
    return add(*this, other);
}

Array Array::substract(const Array& other) const
{
    return substract(*this, other);
}

/*
Array Array::mult(const Array& other) const
{
    return mult(*this, other);
}

Array Array::divide(const Array& other) const
{
    return divide(*this, other);
}
*/

bool Array::equals(const Array& other) const
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

bool Array::lessThan(const Array& other) const
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

bool Array::greaterThan(const Array& other) const
{
    return other.lessThan(*this);
}

std::string Array::toString() const
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

