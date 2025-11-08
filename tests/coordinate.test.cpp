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

#include <text/coordinate.hpp>

#include <gtest/gtest.h>

#include <cstdint>
#include <utils/err.hpp>

using namespace Text;
using namespace std;










// PREDEFINED COORDINATES
Coordinate c00   = 0;
Coordinate c01   = 1;
Coordinate c02   = 2;
Coordinate c03   = 3;
Coordinate c04   = 4;
Coordinate c05   = 5;
Coordinate c06   = 6;
Coordinate c07   = 7;
Coordinate c08   = 8;
Coordinate c09   = 9;
Coordinate c10   = 10;
Coordinate c11   = 11;
Coordinate c12   = 12;
Coordinate c13   = 13;
Coordinate c14   = 14;
Coordinate c15   = 15;
Coordinate c16   = 16;
Coordinate c32   = 32;
Coordinate c64   = 64;
Coordinate c128  = 128;
Coordinate c256  = 256;
Coordinate c512  = 512;
Coordinate c1024 = 1024;










TEST(CoordinateBasicTests, standard_constructor)
{
  constexpr const int NEG_5 = -5;

  EXPECT_NO_THROW(Coordinate coord);
  EXPECT_NO_THROW(Coordinate coord(1));
  EXPECT_NO_THROW(Coordinate coord{ 1 });
  EXPECT_THROW(Coordinate coord(-2), X_);    // Exception Tests
  EXPECT_THROW(Coordinate coord{ -1 }, X_);  // Exception Tests
  EXPECT_THROW(Coordinate coord(NEG_5), X_);
}










TEST(CoordinateBasicTests, accessors)
{
  Coordinate one(1);
  Coordinate two(2);
  Coordinate three(3);
  Coordinate four(4);

  EXPECT_EQ(c01.get(), one.get());
  EXPECT_EQ(c02.get(), two.get());

  EXPECT_EQ(c03(), three());
  EXPECT_EQ(c04(), four());
}










TEST(CoordinateBasicTests, set_func)
{
  // Mutation was tested in large part when the assignment
  // operators were tested
  Coordinate alpha;
  Coordinate beta;
  Coordinate gamma;
  Coordinate delta;

  EXPECT_NO_THROW(alpha.set(1));

  beta.set(1);
  gamma.set(2);
  delta.set(3);

  EXPECT_EQ(beta(), 1);
  EXPECT_EQ(gamma(), 2);
  EXPECT_EQ(delta(), 3);

  EXPECT_THROW(alpha.set(-1), X_);              // Exception Tests
  EXPECT_THROW(alpha.set(-9999999999999), X_);  // Exception Tests
}










TEST(CoordinateBasicTests, assignment_operator)
{
  Coordinate alpha;
  Coordinate beta;
  Coordinate gamma;
  Coordinate delta;

  EXPECT_NO_THROW(alpha = 1);

  beta  = 1;
  gamma = 2;
  delta = 3;

  EXPECT_EQ(beta(), 1);
  EXPECT_EQ(gamma(), 2);
  EXPECT_EQ(delta(), 3);

  EXPECT_THROW(alpha = -1, X_);               // Exception Tests
  EXPECT_THROW(Coordinate epsilon = -2, X_);  // Exception Tests
}










TEST(CoordinateBasicTests, copy_assignment_operator)
{
  // Mutation was tested in large part when the assignment
  // operators were tested
  Coordinate alpha;
  Coordinate beta;
  Coordinate gamma;
  Coordinate delta;

  EXPECT_NO_THROW(alpha = 1);

  beta  = c01;
  gamma = c02;
  delta = c03;

  EXPECT_EQ(beta(), 1);
  EXPECT_EQ(gamma(), 2);
  EXPECT_EQ(delta(), 3);
}










TEST(CoordinateBasicTests, copy_constructor)
{
  Coordinate alpha(123);
  Coordinate beta = alpha;

  EXPECT_TRUE(alpha() == beta());
}










/*




*==========================================================*
NOTE: The Coordinate Comparison Operator tests below use a
pair of characters as their method for communicating which
operators are being tested in each test.

If you look at the first test under this comment the name is
'equality_operator_CC' which means that the test is testing
the overloaded equality operator for comparing Coordinate
against Coordinate, hence the 'CC' at the end.

    * [CC] = COORDINATE COORDINATE
    * [CI] = COORDINATE INTEGER
    * [IC] = INTEGER COORDINATE

The readme file documents and defines the `<Integral>` type.
@SEE -> README.md for more information.
*==========================================================*/










/*

------------------------------------------------------------
* [C|C] COMPARISON
------------------------------------------------------------   */
TEST(CoordinateComparison_CC, equality_op)
{
  // TEST USING PREDEFINED
  EXPECT_EQ(c01, c01);
  EXPECT_EQ(c02, c02);
  EXPECT_EQ(c03, c03);

  // TEST FOR FALSE POSITIVES
  EXPECT_FALSE(Coordinate(0) == Coordinate(1));
  EXPECT_FALSE(Coordinate(1) == Coordinate(2));
  EXPECT_FALSE(Coordinate(2) == Coordinate(3));
}










TEST(CoordinateComparison_CC, no_equality_op)
{
  // TEST USING PREDEFINED
  EXPECT_NE(c01, c02);
  EXPECT_NE(c02, c03);
  EXPECT_NE(c03, c04);

  // TEST FOR FALSE POSITIVES
  EXPECT_FALSE(Coordinate(1) != Coordinate(1));
  EXPECT_FALSE(Coordinate(2) != Coordinate(2));
  EXPECT_FALSE(Coordinate(3) != Coordinate(3));
}










TEST(CoordinateComparison_CC, greater_op)
{
  // GREATER
  EXPECT_TRUE (c03 > c00);  // (3 > 0) -> T
  EXPECT_TRUE (c03 > c01);  // (3 > 1) -> T
  EXPECT_TRUE (c03 > c02);  // (3 > 2) -> T
  EXPECT_FALSE(c03 > c03);  // (3 > 3) -> F
  EXPECT_FALSE(c03 > c04);  // (3 > 4) -> F
  EXPECT_FALSE(c03 > c05);  // (3 > 5) -> F

  EXPECT_TRUE (c01 > c00);  // (0 > 1) -> T
  EXPECT_FALSE(c01 > c01);  // (1 > 1) -> F
  EXPECT_FALSE(c01 > c02);  // (1 > 0) -> T
}










TEST(CoordinateComparison_CC, greater_or_equal_op)
{
  // GREATER
  EXPECT_FALSE(c03 >= c05);  // (3 >= 5) -> T
  EXPECT_FALSE(c04 >= c05);  // (4 >= 5) -> T
  EXPECT_TRUE (c05 >= c05);  // (5 >= 5) -> T
  EXPECT_TRUE (c06 >= c05);  // (6 >= 5) -> F
  EXPECT_TRUE (c07 >= c05);  // (7 >= 5) -> F

  EXPECT_TRUE(c00 >= c00);   // (0 >= 0) -> T
  EXPECT_TRUE(c01 >= c00);   // (1 >= 0) -> F
  EXPECT_TRUE(c02 >= c00);   // (2 >= 0) -> F
}










TEST(CoordinateComparison_CC, lesser_op)
{
  // LESSER
  EXPECT_FALSE(c03 < c01);  // (3 < 1) -> F
  EXPECT_FALSE(c03 < c02);  // (3 < 2) -> F
  EXPECT_FALSE(c03 < c03);  // (3 < 3) -> F
  EXPECT_TRUE (c03 < c04);  // (3 < 4) -> T

  EXPECT_TRUE (c09 < c10);  // ( 9 < 10) -> T
  EXPECT_FALSE(c10 < c10);  // (10 < 10) -> F
  EXPECT_FALSE(c11 < c10);  // (11 < 10) -> F
  EXPECT_FALSE(c12 < c10);  // (12 < 10) -> F
}










TEST(CoordinateComparison_CC, lesser_or_equal_op)
{

  // LESSER OR EQUAL #1
  EXPECT_TRUE (c01 <= c02); // (1 < 2) -> T
  EXPECT_TRUE (c02 <= c02); // (2 < 2) -> T
  EXPECT_FALSE(c03 <= c02); // (3 < 2) -> F

  EXPECT_FALSE(c05 <= c04); // (5 < 4) -> T
  EXPECT_TRUE (c05 <= c05); // (5 < 5) -> T
  EXPECT_TRUE (c05 <= c06); // (5 < 6) -> F
}










/*


------------------------------------------------------------
* [C|I] COMPARISON
------------------------------------------------------------   */
TEST(CoordinateComparison_CI, equality_op)
{
  // EQUALITY
  EXPECT_EQ(c01, 1);
  EXPECT_EQ(c02, 2);
  EXPECT_EQ(c03, 3);

  EXPECT_FALSE(c02 == 0);  // (2 == 0) -> F
  EXPECT_FALSE(c02 == 1);  // (2 == 1) -> F
  EXPECT_TRUE (c02 == 2);  // (2 == 2) -> T
  EXPECT_FALSE(c02 == 3);  // (2 == 3) -> F
}









TEST(CoordinateComparison_CI, no_equality_op)
{
  // EQUALITY
  EXPECT_NE(c01, 0);
  EXPECT_NE(c02, 0);
  EXPECT_NE(c03, 0);

  EXPECT_TRUE (c02 != 0);  // (2 == 0) -> T
  EXPECT_TRUE (c02 != 1);  // (2 == 1) -> T
  EXPECT_FALSE(c02 != 2);  // (2 == 2) -> F
  EXPECT_TRUE (c02 != 3);  // (2 == 3) -> T
}









TEST(CoordinateComparison_CI, greater_op)
{
  EXPECT_TRUE (c02 > 1);  // (2 > 1) -> T
  EXPECT_FALSE(c02 > 2);  // (2 > 2) -> F
  EXPECT_FALSE(c02 > 3);  // (2 > 3) -> F

  EXPECT_FALSE(c05 > 6); // (5 > 6) -> F
  EXPECT_FALSE(c05 > 5); // (5 > 5) -> F
  EXPECT_TRUE (c05 > 4); // (5 > 4) -> T
  EXPECT_TRUE (c05 > 3); // (5 > 3) -> T
  EXPECT_TRUE (c05 > 2); // (5 > 2) -> T
}










TEST(CoordinateComparison_CI, greater_or_equal_op)
{
  EXPECT_TRUE (c02 >= 1);  // (2 >= 1) -> T
  EXPECT_TRUE (c02 >= 2);  // (2 >= 2) -> T
  EXPECT_FALSE(c02 >= 3);  // (2 >= 3) -> F

  EXPECT_FALSE(c05 >= 6);  // (5 >= 6) -> F
  EXPECT_TRUE (c05 >= 5);  // (5 >= 5) -> T
  EXPECT_TRUE (c05 >= 4);  // (5 >= 4) -> T
  EXPECT_TRUE (c05 >= 3);  // (5 >= 3) -> T
  EXPECT_TRUE (c05 >= 2);  // (5 >= 2) -> T
}









TEST(CoordinateComparison_CI, lesser_op)
{
  EXPECT_FALSE(c02 < 1);  // (2 < 1) -> F
  EXPECT_FALSE(c02 < 2);  // (2 < 2) -> F
  EXPECT_TRUE (c02 < 3);  // (2 < 3) -> T


  EXPECT_TRUE (c00 < 2);  // (0 < 2) -> T
  EXPECT_TRUE (c01 < 2);  // (1 < 2) -> T
  EXPECT_FALSE(c02 < 2);  // (2 < 2) -> F
  EXPECT_FALSE(c03 < 2);  // (3 < 2) -> F
  EXPECT_FALSE(c04 < 2);  // (4 < 2) -> F
}










TEST(CoordinateComparison_CI, lesser_or_equal_op)
{
  EXPECT_FALSE(c02 <= 1);  // (2 <= 1) -> F
  EXPECT_TRUE (c02 <= 2);  // (2 <= 2) -> T
  EXPECT_TRUE (c02 <= 3);  // (2 <= 3) -> T

  EXPECT_TRUE (c00 <= 2);  // (0 <= 2) -> T
  EXPECT_TRUE (c01 <= 2);  // (1 <= 2) -> T
  EXPECT_TRUE (c02 <= 2);  // (2 <= 2) -> T
  EXPECT_FALSE(c03 <= 2);  // (3 <= 2) -> F
  EXPECT_FALSE(c04 <= 2);  // (4 <= 2) -> F
}

















/*


------------------------------------------------------------
* [C|I] COMPARISON
------------------------------------------------------------   */
TEST(CoordinateComparison_IC, equality_op)
{
  // EQUALITY
  EXPECT_EQ(2, c02);
  EXPECT_EQ(4, c04);
  EXPECT_EQ(6, c06);

  EXPECT_FALSE(3 == c01);  // F
  EXPECT_FALSE(3 == c02);  // F
  EXPECT_TRUE (3 == c03);  // T
  EXPECT_FALSE(3 == c04);  // F
}










TEST(CoordinateComparison_IC, no_equality_op)
{
  // EQUALITY
  EXPECT_NE(0, c01);
  EXPECT_NE(0, c02);
  EXPECT_NE(0, c03);

  EXPECT_TRUE (2 != c01);  // (2 != 1) -> T
  EXPECT_FALSE(2 != c02);  // (2 != 2) -> F
  EXPECT_TRUE (2 != c03);  // (2 != 3) -> T
  EXPECT_TRUE (2 != c04);  // (2 != 4) -> T
}










TEST(CoordinateComparison_IC, greater_op)
{
  EXPECT_FALSE(0 > c01);  // (0 > 1) -> F
  EXPECT_FALSE(1 > c01);  // (1 > 1) -> F
  EXPECT_TRUE (2 > c01);  // (2 > 1) -> T

  EXPECT_FALSE(2 > c03);  // (2 > 3) -> F
  EXPECT_FALSE(3 > c03);  // (3 > 3) -> F
  EXPECT_TRUE (4 > c03);  // (4 > 3) -> T
}










TEST(CoordinateComparison_IC, greater_or_equal_op)
{
  EXPECT_FALSE(0 >= c01);  // (0 >= 1) -> F
  EXPECT_TRUE (1 >= c01);  // (1 >= 1) -> T
  EXPECT_TRUE (2 >= c01);  // (2 >= 1) -> T

  EXPECT_TRUE (2 >= c01);  // (2 >= 1) -> T
  EXPECT_TRUE (2 >= c02);  // (2 >= 2) -> T
  EXPECT_FALSE(2 >= c03);  // (2 >= 3) -> F

  EXPECT_FALSE(1 >= c02);  // (1 >= 2) -> F
  EXPECT_TRUE (2 >= c02);  // (2 >= 2) -> T
  EXPECT_TRUE (3 >= c02);  // (3 >= 2) -> T
}









TEST(CoordinateComparison_IC, lesser_op)
{
  EXPECT_FALSE(1 < c00);  // (1 < 0) -> F
  EXPECT_FALSE(1 < c01);  // (1 < 1) -> F
  EXPECT_TRUE (1 < c02);  // (1 < 2) -> T

  EXPECT_TRUE (-1 < c01);  // (-1 < 1) -> T
  EXPECT_TRUE ( 0 < c01);  // ( 0 < 1) -> T
  EXPECT_FALSE( 1 < c01);  // ( 1 < 1) -> F
  EXPECT_FALSE( 2 < c01);  // ( 2 < 1) -> F
}










TEST(CoordinateComparison_IC, lesser_or_equal_op)
{

  EXPECT_TRUE (-1 <= c00);  // (0 <= 2) -> T
  EXPECT_TRUE ( 0 <= c00);  // (0 <= 2) -> T
  EXPECT_FALSE( 1 <= c00);  // (1 <= 2) -> F

  EXPECT_TRUE (10 <= c10);  // (2 <= 2) -> T
  EXPECT_FALSE(10 <= c09);  // (3 <= 2) -> F
  EXPECT_FALSE(10 <= c08);  // (4 <= 2) -> F
}










TEST(CoordinateArithmetic_CC, addition)
{
    EXPECT_EQ(c01 + c10, c11);  // (1 + 10) -> 11
    EXPECT_EQ(c02 + c10, c12);  // (2 + 10) -> 12
    EXPECT_EQ(c03 + c10, c13);  // (3 + 10) -> 13
    EXPECT_EQ(c04 + c10, c14);  // (4 + 10) -> 14
    EXPECT_EQ(c05 + c10, c15);  // (5 + 10) -> 15

}










TEST(CoordinateArithmetic_CC, subtraction)
{
    // The EXPECT_THROW tests ensures that an exception is thrown
    // if an operation would result in a negative Coordinate value.
    EXPECT_THROW(c00 - c01, X_ );  //  (0 - 1) -> Ex
    EXPECT_EQ   (c01 - c01, c00);  //  (1 - 1) -> 0
    EXPECT_EQ   (c02 - c01, c01);  //  (2 - 1) -> 1

    EXPECT_EQ   (c03 - c00, c03);  //  (3 - 0) -> 3
    EXPECT_EQ   (c03 - c01, c02);  //  (3 - 1) -> 2
    EXPECT_EQ   (c03 - c02, c01);  //  (3 - 2) -> 1
    EXPECT_EQ   (c03 - c03, c00);  //  (3 - 3) -> 0
    EXPECT_THROW(c03 - c04, X_ );  //  (3 - 4) -> Ex
    EXPECT_THROW(c03 - c05, X_ );  //  (3 - 5) -> Ex
}










TEST(CoordinateArithmetic_CC, multiplication)
{

    EXPECT_EQ(c00 * c04, c00);  // (0 * 4) -> 0
    EXPECT_EQ(c01 * c04, c04);  // (1 * 4) -> 4
    EXPECT_EQ(c02 * c04, c08);  // (2 * 4) -> 8
    EXPECT_EQ(c03 * c04, c12);  // (3 * 4) -> 12

    EXPECT_EQ(c08 * c00,  c00);  // (8 *  0) -> 00
    EXPECT_EQ(c08 * c01,  c08);  // (8 *  1) -> 08
    EXPECT_EQ(c08 * c02,  c16);  // (8 *  2) -> 16
    EXPECT_EQ(c08 * c04,  c32);  // (8 *  4) -> 32
    EXPECT_EQ(c08 * c08,  c64);  // (8 *  8) -> 64
    EXPECT_EQ(c08 * c16, c128);  // (8 * 16) -> 128
}










TEST(CoordinateArithmetic_CC, division) {
    EXPECT_NO_THROW(c00 / c01);  // Dividing into zero should not throw

    EXPECT_THROW(c00 / c00, X_);  // Division by zero should throw
    EXPECT_THROW(c01 / c00, X_);  // Division by zero should throw

    EXPECT_EQ(c00 / c02, c00);  // (00 / 2) -> 0
    EXPECT_EQ(c05 / c02, c02);  // (05 / 2) -> 2
    EXPECT_EQ(c09 / c02, c04);  // (09 / 2) -> 4
    EXPECT_EQ(c13 / c02, c06);  // (13 / 2) -> 6
}










TEST(CoordinateArithmetic_CI, addition)
{
    EXPECT_EQ   (c03 +  2, c05);  // (3 +  2) ->  5
    EXPECT_EQ   (c02 +  1, c03);  // (2 +  1) ->  3
    EXPECT_EQ   (c01 +  0, c01);  // (1 +  0) ->  1
    EXPECT_THROW(c00 + -1,  X_);  // (0 + -1) -> -1 (THROWS EXCEPTION)

    // Make sure negative numbers on rightside don't throw errors if
    // the result is a non-negative Coordinate.
    EXPECT_NO_THROW(c02 + -2);
    EXPECT_NO_THROW(c03 + -3);
    EXPECT_EQ(c02 + -2, c00);  // (2 + -2) -> 0
    EXPECT_EQ(c03 + -3, c00);  // (3 + -3) -> 0
}










TEST(CoordinateArithmetic_CI, subtraction)
{
    EXPECT_EQ   (c02 -  0, c02);  // (2 -  0) ->  2
    EXPECT_EQ   (c02 -  1, c01);  // (2 -  1) ->  1
    EXPECT_EQ   (c02 -  2, c00);  // (2 -  2) ->  0
    EXPECT_THROW(c02 -  3, X_);   // (2 -  3) -> -1 (THROWS EXCEPTION)
    EXPECT_THROW(c02 -  4, X_);   // (2 -  3) -> -2 (THROWS EXCEPTION)
}










TEST(CoordinateArithmetic_CI, multiplication)
{
    EXPECT_EQ(   c03 *  2, c06); // (3 *  2) ->  6
    EXPECT_EQ(   c03 *  1, c03); // (3 *  1) ->  3
    EXPECT_EQ(   c03 *  0, c00); // (3 *  0) ->  0
    EXPECT_THROW(c03 * -1, X_);  // (3 * -1) -> -3 (THROWS EXCEPTION)
    EXPECT_THROW(c03 * -2, X_);  // (3 * -2) -> -6 (THROWS EXCEPTION)
}










TEST(CoordinateArithmetic_CI, division)
{
    EXPECT_EQ   (c06 / 3, c02);  // (6 / 3) -> 2
    EXPECT_EQ   (c06 / 2, c03);  // (6 / 2) -> 3
    EXPECT_EQ   (c06 / 1, c06);  // (6 / 1) -> 6
    EXPECT_THROW(c06 / 0, X_);   // (6 / 0) NOT A REAL NUM -> (THROWS EXCEPTION)
    EXPECT_THROW(c06 /-1, X_);   // (6 /-1) -> -6 (THROWS EXCEPTION)
    EXPECT_THROW(c06 /-2, X_);   // (6 /-2) -> -3 (THROWS EXCEPTION)
}









TEST(CoordinateArithmetic_IC, addition)
{
    // negative addition should throw
    EXPECT_EQ   ( 3 + c04, c07);  // (3 +  4) -> 7
    EXPECT_EQ   ( 2 + c03, c05);  // (2 +  3) -> 5
    EXPECT_EQ   ( 1 + c02, c03);  // (1 +  2) -> 3
    EXPECT_EQ   ( 0 + c01, c01);  // (0 +  1) -> 1
    EXPECT_THROW(-1 + c00,  X_);  // (-1 + 0) -> -1 (THROWS EXCEPTION)

    // Make sure negative numbers on rightside don't throw errors if
    // the result is a non-negative Coordinate.
    EXPECT_NO_THROW(-2 + c02);
    EXPECT_NO_THROW(-3 + c03);
    EXPECT_EQ      (-2 + c02, c00);  // (2 + -2) -> 0
    EXPECT_EQ      (-3 + c03, c00);  // (3 + -3) -> 0
}










TEST(CoordinateArithmetic_IC, subtraction)
{
    EXPECT_THROW(0 - c01, X_);   // (0 - 1) -> -1 (THROWS EXCEPTION)
    EXPECT_EQ   (1 - c01, c00);  // (1 - 1) ->  0
    EXPECT_EQ   (2 - c01, c01);  // (2 - 2) ->  1
    EXPECT_EQ   (3 - c01, c02);  // (3 - 3) ->  2
}










TEST(CoordinateArithmetic_IC, multiplication)
{
    EXPECT_EQ(    2 * c02, c04); // ( 2 * 2) ->  4
    EXPECT_EQ(    1 * c02, c02); // ( 1 * 2) ->  2
    EXPECT_EQ(    0 * c02, c00); // ( 0 * 2) ->  0
    EXPECT_THROW(-1 * c02, X_);  // (-1 * 2) -> -2 (THROWS EXCEPTION)
    EXPECT_THROW(-2 * c02, X_);  // (-2 * 2) -> -4 (THROWS EXCEPTION)
}










TEST(CoordinateArithmetic_IC, division)
{
    EXPECT_EQ   ( 6 / c03, c02);  // ( 6 / 3) ->  2
    EXPECT_EQ   ( 3 / c03, c01);  // ( 3 / 3) ->  1
    EXPECT_EQ   ( 0 / c03, c00);  // ( 0 / 3) ->  0
    EXPECT_THROW(-3 / c03, X_);   // (-3 / 3) -> -1 (THROWS EXCEPTION)
    EXPECT_THROW(-6 / c03, X_);   // (-6 / 3) -> -2 (THROWS EXCEPTION)

    EXPECT_THROW(100 / c00, X_);  // Division by zero should throw
}










TEST(CoordinateIncrementalOps, increment)
{
    Coordinate coord(5);
    EXPECT_EQ(++coord, Coordinate(6));
    EXPECT_EQ(++coord, Coordinate(7));
    EXPECT_EQ(++coord, Coordinate(8));
}










TEST(CoordinateIncrementalOps, decrement)
{
    Coordinate coord(5);
    EXPECT_EQ(--coord, Coordinate(4));
    EXPECT_EQ(--coord, Coordinate(3));
    EXPECT_EQ(--coord, Coordinate(2));
    EXPECT_EQ(--coord, Coordinate(1));
    EXPECT_EQ(--coord, Coordinate(0));
    EXPECT_EQ(--coord, Coordinate(0));
    EXPECT_EQ(--coord, Coordinate(0));
    EXPECT_EQ(--coord, Coordinate(0));
    EXPECT_EQ(--coord, Coordinate(0));
}