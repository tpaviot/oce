#include <gtest/gtest.h>

/*
This example demonstrates how to use gtest to conduct C++ unittesting
with CTest/CMake.
A TestSuite is by definition composed of several testCases.
Declare a first test:
  - TestSuite is CamelCase
  - testCase1 is camelCase
  
In the following, ASSERT_* is stronger than EXPECT_*
*/

TEST(TestSuite, testNullPointer)
{
    int *i=NULL;
    ASSERT_EQ(NULL,i);
}

TEST(TestSuite, testFloatEq)
{
    ASSERT_EQ(1.0, 1.0);
}

TEST(TestSuite, testFloatNeq)
{
    EXPECT_NE(.5, 1.);
}

TEST(TestSuite, testBoolean)
{
    bool b = true;
    EXPECT_TRUE(b);
}

TEST(TestSuite, testIntegerLighter)
{
    int a=1,b=2;
    EXPECT_LT(a,b);
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

