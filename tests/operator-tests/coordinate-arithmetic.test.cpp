/****************************************************************
 * PROJECT:     'TextBuffer'
 * FILEPATH:    'tests/coordinate-operator-EQ.test.cpp'
 * REPOSITORY:  'https://github.com/AjayChambers/TextBuffer'
 * COPYRIGHT:   'GPL-3.0'
 * AUTHOR:      'Andrew Jay Chambers'
 * CONTACT:     'w3dojo@gmail.com'
 * DESCRIPTION:
 *  This file tests that Coordinate objects are equipped with an
 *  overloaded add (+) operator that works with 'int' literals,
 *  explicit 'size_t' values, and other Coordinate objects.
 ****************************************************************/

//==============================================================*
// Test@ "Coordinate |> Operator |> Add (+)"
//==============================================================*

#include "../include/utils/ex.hpp"
#include "../test-object/comparison-test-case.hpp"

#include <coordinate.hpp>

#include <gtest/gtest.h>

using namespace Text;
using namespace std;
using namespace TextBufferProj;


class CoordinateArithmeticTest : public ::testing::Test
{
   protected:
    Coordinate c0{ 0 };
    Coordinate c1{ 1 };
    Coordinate c2{ 2 };
    Coordinate c3{ 3 };
    Coordinate c4{ 4 };
    Coordinate c5{ 5 };
    Coordinate c6{ 6 };
    Coordinate c7{ 7 };
    Coordinate c8{ 8 };
    Coordinate c9{ 9 };
    Coordinate c10{ 10 };

    size_t s0 = 0;
    size_t s1 = 1;
    size_t s2 = 2;
    size_t s3 = 3;
    size_t s4 = 4;
    size_t s5 = 5;
};






TEST_F(CoordinateArithmeticTest, OperatorAddition) {
    // TESTING ADDITION OPERATOR
    EXPECT_EQ(c1 + 0, c1);
    EXPECT_EQ(c2 + 1, c3);
    EXPECT_EQ(1 + c5, c6);
    EXPECT_EQ(1 + c6, c7);
    EXPECT_EQ(-3 + c4, c1);

    EXPECT_EQ(c2 + s4, c6);
    EXPECT_EQ(c4 + s3, c7);
    EXPECT_EQ(c6 + s2, c8);
    EXPECT_EQ(s2 + c8, c10);
    EXPECT_EQ(s1 + c9, c10);
    EXPECT_EQ(s0 + c10, c10);

    // EXCEPTION TESTING
    EXPECT_THROW(c9 + (-80), EX);
    EXPECT_THROW(c5 + (-6), EX);
    EXPECT_THROW((-2) + c1, EX);
    EXPECT_THROW((-3) + c2, EX);
}






TEST_F(CoordinateArithmeticTest, OperatorSubtraction) {
    // TESTING SUBTRACTION OPERATOR
    EXPECT_EQ(c10 - 10, c0);
    EXPECT_EQ(c9 - 8, c1);
    EXPECT_EQ(c2 - (-3), c5);
    EXPECT_EQ(10 - c7, c3);
    EXPECT_EQ(10 - c6, c4);

    EXPECT_EQ(c4 - s2, c2);
    EXPECT_EQ(c3 - s2, c1);
    EXPECT_EQ(s5 - c4, c1);
    EXPECT_EQ(s4 - c3, c1);


    // EXCEPTION TESTING
    EXPECT_THROW(c9 - 80, EX);
    EXPECT_THROW(c5 - 6, EX);
    EXPECT_THROW(2 - c3, EX);
    EXPECT_THROW(3 - c4, EX);
}