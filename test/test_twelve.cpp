#include <gtest/gtest.h>
#include "twelve.hpp"

TEST(ArrayTest, DefaultConstructor) {
    Array num;
    EXPECT_EQ(num.getSize(), 0);
}

TEST(ArrayTest, SizeConstructor) {
    Array num(3, 5);
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "555");
}

TEST(ArrayTest, StringConstructorValid) {
    Array num("12A");
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "12A");
}

TEST(ArrayTest, StringConstructorInvalid) {
    EXPECT_THROW(Array num("12G"), std::invalid_argument);
}

TEST(ArrayTest, InitializerListConstructor) {
    Array num{10, 2, 1};
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.toString(), "12A");
}

TEST(ArrayTest, Equals) {
    Array num1("12A");
    Array num2("12A");
    Array num3("12B");
    
    EXPECT_TRUE(num1.equals(num2));
    EXPECT_FALSE(num1.equals(num3));
}

TEST(ArrayTest, LessThan) {
    Array num1("12A");
    Array num2("12B");
    Array num3("13A");
    
    EXPECT_TRUE(num1.lessThan(num2));
    EXPECT_TRUE(num2.lessThan(num3));
    EXPECT_FALSE(num3.lessThan(num1));
}

TEST(ArrayTest, GreaterThan) {
    Array num1("12B");
    Array num2("12A");
    Array num3("11B");
    
    EXPECT_TRUE(num1.greaterThan(num2));
    EXPECT_TRUE(num2.greaterThan(num3));
    EXPECT_FALSE(num3.greaterThan(num1));
}

TEST(ArrayTest, Addition) {
    Array num1("5");
    Array num2("7");
    Array result = num1.add(num2);
    EXPECT_EQ(result.toString(), "10");
    
    Array num3("A");
    Array num4("3");
    result = num3.add(num4);
    EXPECT_EQ(result.toString(), "11");
    
    Array num5("1B");
    Array num6("5");
    result = num5.add(num6);
    EXPECT_EQ(result.toString(), "24");
}

TEST(ArrayTest, Subtraction) {
    Array num1("A");
    Array num2("5");
    Array result = num1.substract(num2);
    EXPECT_EQ(result.toString(), "5");
    
    Array num3("15");
    Array num4("A");
    result = num3.substract(num4);
    EXPECT_EQ(result.toString(), "7");
}

TEST(ArrayTest, ZeroOperations) {
    Array zero("0");
    Array num("12A");

    Array result_sum = num.add(zero);
    EXPECT_EQ(result_sum.toString(), "12A");

    Array result_sub = num.substract(zero);
    EXPECT_EQ(result_sub.toString(), "12A");
    
}

TEST(ArrayTest, LargeNumbers) {
    Array num1("1000000");
    Array num2("1");
    Array result_sum = num1.add(num2);
    EXPECT_EQ(result_sum.toString(), "1000001");
    
    Array result_sub = num1.substract(num2);
    EXPECT_EQ(result_sub.toString(), "BBBBBB");
}

TEST(ArrayTest, CopyConstructor) {
    Array original("12AB");
    Array copy(original);
    
    EXPECT_TRUE(original.equals(copy));
    EXPECT_EQ(original.toString(), copy.toString());
}

TEST(ArrayTest, AssignmentOperator) {
    Array original("12AB");
    Array assigned;
    assigned = original;
    
    EXPECT_TRUE(original.equals(assigned));
    EXPECT_EQ(original.toString(), assigned.toString());
}
