#include <gtest/gtest.h>
#include "twelve.hpp"

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    EXPECT_EQ(Twelve::getSize(num), 1);
    EXPECT_EQ(Twelve::toString(num), "0");
}

TEST(TwelveTest, SizeConstructor) {
    Twelve num(3, 5);
    EXPECT_EQ(Twelve::getSize(num), 3);
    EXPECT_EQ(Twelve::toString(num), "555");
}

TEST(TwelveTest, StringConstructorValid) {
    Twelve num("12A");
    EXPECT_EQ(Twelve::getSize(num), 3);
    EXPECT_EQ(Twelve::toString(num), "12A");
}

TEST(TwelveTest, StringConstructorInvalid) {
    EXPECT_THROW(Twelve num("12G"), std::invalid_argument);
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num{1, 2, 10}; 
    EXPECT_EQ(Twelve::getSize(num), 3);
    EXPECT_EQ(Twelve::toString(num), "12A");
}

TEST(TwelveTest, Equals) {
    Twelve num1("12A");
    Twelve num2("12A");
    Twelve num3("12B");
    
    EXPECT_TRUE(Twelve::equals(num1, num2));
    EXPECT_FALSE(Twelve::equals(num1, num3));
}

TEST(TwelveTest, LessThan) {
    Twelve num1("12A");
    Twelve num2("12B");
    Twelve num3("13A");
    
    EXPECT_TRUE(Twelve::lessThan(num1, num2));
    EXPECT_TRUE(Twelve::lessThan(num2, num3));
    EXPECT_FALSE(Twelve::lessThan(num3, num1));
}

TEST(TwelveTest, GreaterThan) {
    Twelve num1("12B");
    Twelve num2("12A");
    Twelve num3("11B");
    
    EXPECT_TRUE(Twelve::greaterThan(num1, num2));
    EXPECT_TRUE(Twelve::greaterThan(num2, num3));
    EXPECT_FALSE(Twelve::greaterThan(num3, num1));
}

TEST(TwelveTest, Addition) {
    Twelve num1("5");
    Twelve num2("7");
    Twelve result_add2 = Twelve::add(num1, num2);
    EXPECT_EQ(Twelve::toString(result_add2), "10");
    
    Twelve num3("A");
    Twelve num4("3");
    Twelve result_add4 = Twelve::add(num3, num4);
    EXPECT_EQ(Twelve::toString(result_add4), "11");
    
    Twelve num5("1B");
    Twelve num6("5");
    Twelve result_add6 = Twelve::add(num5, num6);
    EXPECT_EQ(Twelve::toString(result_add6), "24");
}

TEST(TwelveTest, Subtraction) {
    Twelve num1("A");
    Twelve num2("5");
    Twelve result_sub2 = Twelve::substract(num1, num2);
    EXPECT_EQ(Twelve::toString(result_sub2), "5");
    
    Twelve num3("15");
    Twelve num4("A");
    Twelve result_sub4 = Twelve::substract(num3, num4);
    EXPECT_EQ(Twelve::toString(result_sub4), "7");
}

TEST(TwelveTest, SubtractionNegativeResult) {
    Twelve num1("5");
    Twelve num2("A");
    
    EXPECT_THROW(Twelve::substract(num1, num2), std::invalid_argument);
}

TEST(TwelveTest, ZeroOperations) {
    Twelve zero("0");
    Twelve num("12A");

    Twelve result_sum = Twelve::add(num, zero);
    EXPECT_EQ(Twelve::toString(result_sum), "12A");

    Twelve result_sub = Twelve::substract(num, zero);
    EXPECT_EQ(Twelve::toString(result_sub), "12A");
    
    Twelve result_sub2 = Twelve::substract(zero, zero);
    EXPECT_EQ(Twelve::toString(result_sub2), "0");
}

TEST(TwelveTest, LargeNumbers) {
    Twelve num1("1000000");
    Twelve num2("1");
    Twelve result_sum = Twelve::add(num1, num2);
    EXPECT_EQ(Twelve::toString(result_sum), "1000001");
    
    Twelve result_sub = Twelve::substract(num1, num2);
    EXPECT_EQ(Twelve::toString(result_sub), "BBBBBB");
}

TEST(TwelveTest, CopyConstructor) {
    Twelve original("12AB");
    Twelve copy(original);
    
    EXPECT_TRUE(Twelve::equals(original, copy));
    EXPECT_EQ(Twelve::toString(original), Twelve::toString(copy));
}

TEST(TwelveTest, CopyMethod) {
    Twelve original("12AB");
    Twelve copied = Twelve::copy(original);
    
    EXPECT_TRUE(Twelve::equals(original, copied));
    EXPECT_EQ(Twelve::toString(original), Twelve::toString(copied));
    EXPECT_NE(&original, &copied);
}

TEST(TwelveTest, MoveConstructor) {
    Twelve original("12AB");
    Twelve moved(std::move(original));
    
    EXPECT_EQ(Twelve::toString(moved), "12AB");
}

TEST(TwelveTest, IsZero) {
    Twelve zero1("0");
    Twelve zero2(1, 0);
    Twelve nonZero("1");
    
    EXPECT_TRUE(Twelve::isZero(zero1));
    EXPECT_TRUE(Twelve::isZero(zero2));
    EXPECT_FALSE(Twelve::isZero(nonZero));
}

TEST(TwelveTest, CompareAbsolute) {
    Twelve num1("12A");
    Twelve num2("12A");
    Twelve num3("12B");
    Twelve num4("123");
    
    EXPECT_EQ(Twelve::compareAbsolute(num1, num2), 0);
    EXPECT_EQ(Twelve::compareAbsolute(num1, num3), -1);
    EXPECT_EQ(Twelve::compareAbsolute(num3, num1), 1);
    EXPECT_EQ(Twelve::compareAbsolute(num4, num1), -1);
}

TEST(TwelveTest, EdgeCases) {
    Twelve maxDigit("B");
    EXPECT_EQ(Twelve::toString(maxDigit), "B");
    
    Twelve withLeadingZeros("001");
    EXPECT_EQ(Twelve::toString(withLeadingZeros), "1");
    
    Twelve empty("");
    EXPECT_EQ(Twelve::toString(empty), "0");
}

TEST(TwelveTest, ArithmeticChain) {
    Twelve a("5");
    Twelve b("3");
    Twelve c("2");
    
    Twelve result1 = Twelve::add(a, b); 
    Twelve result2 = Twelve::add(result1, c); 
    Twelve result3 = Twelve::substract(result2, a); 
    
    EXPECT_EQ(Twelve::toString(result3), "5");
}

TEST(TwelveTest, AdditionWithCarry) {
    Twelve num1("B");
    Twelve num2("1");
    Twelve result = Twelve::add(num1, num2);
    EXPECT_EQ(Twelve::toString(result), "10");
    
    Twelve num3("BB");
    Twelve num4("1");
    Twelve result2 = Twelve::add(num3, num4);
    EXPECT_EQ(Twelve::toString(result2), "100");
}

TEST(TwelveTest, SubtractionWithBorrow) {
    Twelve num1("10");
    Twelve num2("1");
    Twelve result = Twelve::substract(num1, num2);
    EXPECT_EQ(Twelve::toString(result), "B");
    
    Twelve num3("100");
    Twelve num4("1");
    Twelve result2 = Twelve::substract(num3, num4);
    EXPECT_EQ(Twelve::toString(result2), "BB");
}

TEST(TwelveTest, EqualNumbersComparison) {
    Twelve num1("123AB");
    Twelve num2("123AB");
    
    EXPECT_TRUE(Twelve::equals(num1, num2));
    EXPECT_FALSE(Twelve::lessThan(num1, num2));
    EXPECT_FALSE(Twelve::greaterThan(num1, num2));
}

TEST(TwelveTest, DifferentLengthNumbers) {
    Twelve num1("100");
    Twelve num2("99");
    
    EXPECT_TRUE(Twelve::greaterThan(num1, num2));
    EXPECT_FALSE(Twelve::lessThan(num1, num2));
    EXPECT_FALSE(Twelve::equals(num1, num2));
}