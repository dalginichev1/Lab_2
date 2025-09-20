#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

class Twelve
{
    private:
        size_t size;
        unsigned char * data;

        static Twelve add(const Twelve& a, const Twelve& b);
        static Twelve substract(const Twelve& a, const Twelve& b);
        static Twelve mult(const Twelve& a, const Twelve& b);
        static Twelve div(const Twelve& a, const Twelve& b);
        Twelve multByDigit(unsigned char digit) const;
        void shiftLeft(size_t position);
        static Twelve substractForDivision(const Twelve& a, const Twelve& b);

    public:
        Twelve();
        Twelve(const size_t& n, unsigned char t = 0);
        Twelve(const std::initializer_list<unsigned char>& t);
        Twelve(const std::string& t);
        Twelve(const Twelve& other);
        Twelve(Twelve&& other) noexcept;
        virtual ~Twelve() noexcept;

    size_t getSize() const;

    Twelve copy() const; 

    Twelve add(const Twelve& other) const;
    Twelve substract(const Twelve& other) const;
    Twelve mult(const Twelve& other) const;
    Twelve div(const Twelve& other) const;
    static int compareAbsolute(const Twelve& a, const Twelve& b);

    bool isZero() const;
    bool equals(const Twelve& other) const;
    bool lessThan(const Twelve& other) const;
    bool greaterThan(const Twelve& other) const;

    std::string toString() const;
};