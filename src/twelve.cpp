#include <string>
#include <cstring>
#include <stdexcept>
#include "twelve.hpp"

Twelve::Twelve() : _data(1, 0) {};

Twelve::Twelve(const size_t& n, unsigned char t): _data(n, t) {};

Twelve::Twelve(const std::initializer_list<unsigned char>& t): _data(t.size())
{
    size_t i = t.size() - 1;
    for (auto it = t.begin(); it != t.end(); ++it, --i)
    {
        _data.set(i, *it);
    }
}

Twelve::Twelve(const std::string& s): _data(1, 0)
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
    _data.resize(strSize);

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

        _data.set(strSize - i - 1, value);
    }
}

Twelve::Twelve(const Twelve& other): _data(other._data) {}

Twelve::Twelve(Twelve&& other) noexcept: _data(std::move(other._data)) {}

Twelve::~Twelve() noexcept {}

size_t Twelve::getSize(const Twelve& num) 
{
    return num._data.size();
}

bool Twelve::isZero(const Twelve& num)
{
    return num._data.size() == 1 && num._data.get(0) == 0;
}

int Twelve::compareAbsolute(const Twelve& a, const Twelve& b)
{
    if (a._data.size() > b._data.size()) return 1;
    if (a._data.size() < b._data.size()) return -1;

    for (int i = a._data.size() - 1; i >= 0; --i)
    {
        if (a._data.get(i) > b._data.get(i)) return 1;
        if (a._data.get(i) < b._data.get(i)) return -1;
    }

    return 0;
} 

Twelve Twelve::copy(const Twelve& num) 
{
    return Twelve(num);
}

Twelve Twelve::add(const Twelve& a, const Twelve& b)
{
    size_t maxSize = std::max(a._data.size(), b._data.size());
    Twelve result(maxSize + 1, 0);

    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = (i < a._data.size()) ? a._data.get(i) : 0;
        int digit_b = (i < b._data.size()) ? b._data.get(i) : 0;

        int sum  = digit_a + digit_b + carry;
        result._data.set(i, sum % 12);
        carry = sum / 12;
    }

    if (carry > 0)
    {
        result._data.set(maxSize, carry);
    }
    else
    {
        size_t newSize = maxSize;

        while (newSize > 1 && result._data.get(newSize - 1) == 0)
        {
            --newSize;
        }
        result._data.resize(newSize);
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

    size_t maxSize = a._data.size();
    Twelve result(maxSize, 0);

    int borrow = 0;

    for (size_t i = 0; i < maxSize; ++i)
    {
        int digit_a = a._data.get(i);
        int digit_b = (i < b._data.size()) ? b._data.get(i) : 0;

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

        result._data.set(i, diff);
    }

    size_t newSize = maxSize;
    while(newSize > 1 && result._data.get(newSize - 1) == 0)
    {
        --newSize;
    }

    result._data.resize(newSize);

    return result;
}

bool Twelve::equals(const Twelve& a, const Twelve& b) 
{
    if (a._data.size() != b._data.size())
    {
        return false;
    }

    for (size_t i = 0; i < a._data.size(); ++i)
    {
        if (a._data.get(i) != b._data.get(i))
        {
            return false;
        }
    }

    return true;
}

bool Twelve::lessThan(const Twelve& a, const Twelve& b) 
{
    if (a._data.size() > b._data.size())
    {
        return false;
    }

    if (a._data.size() < b._data.size())
    {
        return true;
    }

    for (int i = a._data.size() - 1; i >= 0; --i)
    {
        if (a._data.get(i) > b._data.get(i))
        {
            return false;
        }
        else if (a._data.get(i) < b._data.get(i))
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
    if (num._data.empty() || (num._data.size() == 1 && num._data.get(0) == 0))
    {
        return "0";
    }

    std::string result;

    for (int i = num._data.size() - 1; i >= 0; --i)
    {
        unsigned char digit = num._data.get(i);
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

