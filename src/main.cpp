#include <iostream>
#include <string>
#include <stdexcept>
#include "twelve.hpp"

void printNumber(const Twelve& num, const std::string& name) {
    std::cout << name << " = " << Twelve::toString(num) << std::endl;
}

Twelve inputNumber(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        try {
            Twelve result(input);
            return result;
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: неверный формат числа. Используйте цифры 0-9 и буквы A-B" << std::endl;
            std::cout << "Попробуйте снова: ";
        }
    }
}

void copyOperation(const Twelve& original)
{
    Twelve copy = Twelve::copy(original);

    printNumber(original, "Original");
    printNumber(copy, "Copy");

    std::cout << "Original's adress: " << &original << std::endl;
    std::cout << "Copy's adress: " << &copy << std::endl;
    std::cout << "Is objects equal?: " << (Twelve::equals(original, copy) ? true : false) << std::endl;

    std::cout << "It is same objects: " << (&original == &copy ? true : false) << std::endl;
}

int main() {
    std::cout << "=== Калькулятор двенадцатеричных чисел ===" << std::endl;
    std::cout << "Доступные операции: +, -, copy, ==, <, >" << std::endl;
    std::cout << "Используйте цифры 0-9 и буквы A-B для ввода чисел" << std::endl << std::endl;

    while (true) {
        try {
            Twelve num1 = inputNumber("Введите первое число: ");
            printNumber(num1, "Первое число");

            std::string operation;
            std::cout << "Введите операцию (+, -, copy, ==, <, >): ";
            std::cin >> operation;

            if (operation == "==" || operation == "<" || operation == ">") {
                Twelve num2 = inputNumber("Введите второе число: ");
                printNumber(num2, "Второе число");

                if (operation == "==") {
                    std::cout << "Результат: " << (Twelve::equals(num1, num2) ? "true" : "false") << std::endl;
                } else if (operation == "<") {
                    std::cout << "Результат: " << (Twelve::lessThan(num1, num2) ? "true" : "false") << std::endl;
                } else if (operation == ">") {
                    std::cout << "Результат: " << (Twelve::greaterThan(num1, num2) ? "true" : "false") << std::endl;
                }
            }
            else if (operation == "copy"){
                copyOperation(num1);
            }
            else {
                Twelve num2 = inputNumber("Введите второе число: ");
                printNumber(num2, "Второе число");

                if (operation == "+") {
                    Twelve result = Twelve::add(num1, num2);
                    std::cout << "Результат сложения: ";
                    printNumber(result, "Результат");
                } else if (operation == "-") {
                    Twelve result = Twelve::substract(num1, num2);
                    std::cout << "Результат вычитания: ";
                    printNumber(result, "Результат");
                } else {
                    std::cout << "Неизвестная операция!" << std::endl;
                    continue;
                }
            }

        } catch (const std::exception& e) {
            std::cout << "Произошла ошибка: " << e.what() << std::endl;
        }

        std::cout << std::endl << "Хотите продолжить? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
        std::cout << std::endl;
    }

    std::cout << "До свидания!" << std::endl;
    return 0;
}