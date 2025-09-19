#include <iostream>
#include <string>
#include <stdexcept>
#include "twelve.hpp"

void printNumber(const Array& num, const std::string& name) {
    std::cout << name << " = " << num.toString() << std::endl;
}

Array inputNumber(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;

        try {
            Array result(input);
            return result;
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: неверный формат числа. Используйте цифры 0-9 и буквы A-B" << std::endl;
            std::cout << "Попробуйте снова: ";
        }
    }
}

int main() {
    std::cout << "=== Калькулятор двенадцатеричных чисел ===" << std::endl;
    std::cout << "Доступные операции: +, -, *, /, ==, <, >" << std::endl;
    std::cout << "Используйте цифры 0-9 и буквы A-B для ввода чисел" << std::endl << std::endl;

    while (true) {
        try {
            Array num1 = inputNumber("Введите первое число: ");
            printNumber(num1, "Первое число");

            std::string operation;
            std::cout << "Введите операцию (+, -, ==, <, >): ";
            std::cin >> operation;

            if (operation == "==" || operation == "<" || operation == ">") {
                Array num2 = inputNumber("Введите второе число: ");
                printNumber(num2, "Второе число");

                if (operation == "==") {
                    std::cout << "Результат: " << (num1.equals(num2) ? "true" : "false") << std::endl;
                } else if (operation == "<") {
                    std::cout << "Результат: " << (num1.lessThan(num2) ? "true" : "false") << std::endl;
                } else if (operation == ">") {
                    std::cout << "Результат: " << (num1.greaterThan(num2) ? "true" : "false") << std::endl;
                }
            } else {
                Array num2 = inputNumber("Введите второе число: ");
                printNumber(num2, "Второе число");

                Array result;

                if (operation == "+") {
                    result = num1.add(num2);
                    std::cout << "Результат сложения: ";
                } else if (operation == "-") {
                    result = num1.substract(num2);
                    std::cout << "Результат вычитания: ";
                } else {
                    std::cout << "Неизвестная операция!" << std::endl;
                    continue;
                }

                printNumber(result, "Результат");
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