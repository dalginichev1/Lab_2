#include <gtest/gtest.h>
#include "twelve.hpp"

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    EXPECT_EQ(num.getSize(), 0);
}

TEST(TwelveTest, SizeConstructor) {
    Twelve num(3, 5);
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "555");
}

TEST(TwelveTest, StringConstructorValid) {
    Twelve num("12A");
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "12A");
}

TEST(TwelveTest, StringConstructorInvalid) {
    EXPECT_THROW(Twelve num("12G"), std::invalid_argument);
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num{10, 2, 1};
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "12A");
}

TEST(TwelveTest, Equals) {
    Twelve num1("12A");
    Twelve num2("12A");
    Twelve num3("12B");
    
    EXPECT_TRUE(num1.equals(num2));
    EXPECT_FALSE(num1.equals(num3));
}

TEST(TwelveTest, LessThan) {
    Twelve num1("12A");
    Twelve num2("12B");
    Twelve num3("13A");
    
    EXPECT_TRUE(num1.lessThan(num2));
    EXPECT_TRUE(num2.lessThan(num3));
    EXPECT_FALSE(num3.lessThan(num1));
}

TEST(TwelveTest, GreaterThan) {
    Twelve num1("12B");
    Twelve num2("12A");
    Twelve num3("11B");
    
    EXPECT_TRUE(num1.greaterThan(num2));
    EXPECT_TRUE(num2.greaterThan(num3));
    EXPECT_FALSE(num3.greaterThan(num1));
}

TEST(TwelveTest, Addition) {
    Twelve num1("5");
    Twelve num2("7");
    Twelve result_add2(num1.add(num2));
    EXPECT_EQ(result_add2.toString(), "10");
    
    Twelve num3("A");
    Twelve num4("3");
    Twelve result_add4(num3.add(num4));
    EXPECT_EQ(result_add4.toString(), "11");
    
    Twelve num5("1B");
    Twelve num6("5");
    Twelve result_add6(num5.add(num6));
    EXPECT_EQ(result_add6.toString(), "24");
}

TEST(TwelveTest, Subtraction) {
    Twelve num1("A");
    Twelve num2("5");
    Twelve result_sub2(num1.substract(num2));
    EXPECT_EQ(result_sub2.toString(), "5");
    
    Twelve num3("15");
    Twelve num4("A");
    Twelve result_sub4(num3.substract(num4));
    EXPECT_EQ(result_sub4.toString(), "7");
}

TEST(TwelveTest, ZeroOperations) {
    Twelve zero("0");
    Twelve num("12A");

    Twelve result_sum(num.add(zero));
    EXPECT_EQ(result_sum.toString(), "12A");

    Twelve result_sub(num.substract(zero));
    EXPECT_EQ(result_sub.toString(), "12A");
    
}

TEST(TwelveTest, LargeNumbers) {
    Twelve num1("1000000");
    Twelve num2("1");
    Twelve result_sum(num1.add(num2));
    EXPECT_EQ(result_sum.toString(), "1000001");
    
    Twelve result_sub(num1.substract(num2));
    EXPECT_EQ(result_sub.toString(), "BBBBBB");
}

TEST(TwelveTest, CopyConstructor) {
    Twelve original("12AB");
    Twelve copy(original);
    
    EXPECT_TRUE(original.equals(copy));
    EXPECT_EQ(original.toString(), copy.toString());
}

TEST(TwelveTest, AssignmentOperator) {
    Twelve original("12AB");
    Twelve assigned(original);
    
    EXPECT_TRUE(original.equals(assigned));
    EXPECT_EQ(original.toString(), assigned.toString());
}
