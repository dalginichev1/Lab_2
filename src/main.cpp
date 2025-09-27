#include <iostream>
#include <string>
#include <stdexcept>
#include "twelve.hpp"

int main() 
{
    std::string input_a;
    std::string input_b;
    std::cin >> input_a;
    std::cin >> input_b;

    Twelve a(input_a);
    Twelve b(input_b);

    Twelve add = Twelve::add(a, b);
    std::cout << Twelve::toString(add) << std::endl;

    Twelve sub = Twelve::substract(a, b);
    std::cout << Twelve::toString(sub) << std::endl;
}