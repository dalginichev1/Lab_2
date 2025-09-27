#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>
#include "array.hpp"

class Twelve
{
    private:

        Array data;

    public:
        Twelve();
        Twelve(const size_t& n, unsigned char t = 0);
        Twelve(const std::initializer_list<unsigned char>& t);
        Twelve(const std::string& t);
        Twelve(const Twelve& other);
        Twelve(Twelve&& other) noexcept;
        virtual ~Twelve() noexcept;

        static size_t getSize(const Twelve& num);
        static Twelve copy(const Twelve& num);

        static Twelve add(const Twelve& a, const Twelve& b);
        static Twelve substract(const Twelve& a, const Twelve& b);

        static int compareAbsolute(const Twelve& a, const Twelve& b);
        static bool equals(const Twelve& a, const Twelve& b);
        static bool lessThan(const Twelve& a, const Twelve& b);
        static bool greaterThan(const Twelve& a, const Twelve& b);

        static std::string toString(const Twelve& num);
};