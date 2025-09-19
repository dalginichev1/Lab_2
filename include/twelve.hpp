#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

class Array
{
    private:
        size_t size;
        unsigned char * data;

        static Array add(const Array& a, const Array& b);
        static Array substract(const Array& a, const Array& b);
        static Array mult(const Array& a, const Array& b);
        static Array div(const Array& a, const Array& b);
        Array multByDigit(unsigned char digit) const;
        void shiftLeft(size_t position);
        static Array substractForDivision(const Array& a, const Array& b);

    public:
        Array();
        Array(const size_t& n, unsigned char t = 0);
        Array(const std::initializer_list<unsigned char>& t);
        Array(const std::string& t);
        Array(const Array& other);
        Array(Array&& other) noexcept;
        virtual ~Array() noexcept;

    size_t getSize() const;

    Array& operator=(const Array& other);
    Array add(const Array& other) const;
    Array substract(const Array& other) const;
    Array mult(const Array& other) const;
    Array div(const Array& other) const;
    static int compareAbsolute(const Array& a, const Array& b);

    bool isZero() const;
    bool equals(const Array& other) const;
    bool lessThan(const Array& other) const;
    bool greaterThan(const Array& other) const;

    std::string toString() const;
};