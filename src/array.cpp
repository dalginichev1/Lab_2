#include <cstddef>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "array.hpp"

void Array::clear()
{
    delete[] data;
    data = nullptr;
}

void Array::copyFrom(const Array& other)
{
    _size = other._size;
    data = new unsigned char[_size];
    std::copy(other.data, other.data + _size, data);
}

Array::Array(): _size(0), data(nullptr) {};

Array::Array(size_t size, unsigned char value): _size(size), data(nullptr)
{
    data = new unsigned char[_size];
    std::fill(data, data + _size, value);
}

Array::Array(const std::initializer_list<unsigned char>& t)
{
    data = new unsigned char[_size];
    size_t i = 0;
    for (unsigned char value: t)
    {
        data[++i] = value;
    }

}

Array::Array(const Array& other): _size(0), data(nullptr)
{
    copyFrom(other);
}

Array::Array(Array&& other) noexcept: _size(other._size), data(other.data)
{
    other._size = 0;
    other.data = nullptr;
}

Array::Array(const std::string& t): _size(t.length()), data(nullptr)
{
    data = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i)
    {
        char c = t[i];
        if (c >= '0' && c <= '9')
        {
            data[_size - i - 1] = c - '0';
        }
        else if (c == 'A' || c == 'a')
        {
            data[_size - i - 1] = 10;
        }
        else
        {
            clear();
            throw std::invalid_argument("Invalid character");
        }
    }
}

unsigned char Array::get(const size_t& index) const
{
    return data[index];
}

void Array::set(const size_t& index, const unsigned char& value) const
{
    data[index] = value;
}

size_t Array::size() const
{
    return _size;
}

bool Array::empty() const
{
    return _size == 0;
}

void Array::resize(size_t newSize, unsigned char value)
{
    unsigned char* newData = new unsigned char[newSize];

    size_t copySize = std::min(_size, newSize);

    if (copySize > 0 && data != nullptr)
    {
        std::copy(data, data + copySize, newData);
    }

    if (newSize > _size)
    {
        std::fill(newData + _size, newData + newSize, value);
    }

    clear();

    data = newData;
    _size = newSize;
}

Array::~Array() noexcept
{
    delete[] data;
}