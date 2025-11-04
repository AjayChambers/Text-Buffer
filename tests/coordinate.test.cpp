
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
#include "utils/err.hpp"

#include <text/coordinate.hpp>

#include <gtest/gtest.h>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>

using namespace Text;
using namespace std;




TEST(Coordinate_Construction, construction_test)
{
  EXPECT_NO_THROW(Coordinate c);
  EXPECT_NO_THROW(Coordinate c(1));
  EXPECT_NO_THROW(Coordinate c{ 2 });
  EXPECT_THROW(Coordinate c(-1), Ex);    // Exception Tests
  EXPECT_THROW(Coordinate c{ -2 }, Ex);  // Exception Tests
}




TEST(Coordinate_Construction, copy_construction_test)
{
  Coordinate c_alpha = 123;
  EXPECT_NO_THROW(Coordinate c_beta(c_alpha));
  EXPECT_NO_THROW(Coordinate c_beta{ c_alpha });
}




TEST(Coordinate_Assignment, assignment_test)
{
  EXPECT_NO_THROW(Coordinate c = 3);
  EXPECT_THROW(Coordinate c = -3, Ex);  // Exception Tests
}




TEST(Coordinate_Assignment, copy_assignment_test)
{
  Coordinate c_alpha = 25;
  EXPECT_NO_THROW(Coordinate c_beta = c_alpha);
  EXPECT_NO_THROW(Coordinate c = Coordinate(50));
  EXPECT_THROW(Coordinate c = Coordinate(-1), Ex);  // Exception Tests
}




TEST(Coordinate_Internal_Access, accessor_test)
{
  Coordinate c_alpha(59444);
  EXPECT_EQ(c_alpha(), 59444);
  EXPECT_EQ(c_alpha.get(), 59444);
}




TEST(Coordinate_Internal_Mutation, mutator_test)
{
  // Mutation was tested in large part when the assignment
  // operators were tested
  Coordinate c_alpha(8);
  EXPECT_EQ(c_alpha(), 8);

  c_alpha.set(0);
  EXPECT_EQ(c_alpha(), 0);

  c_alpha = 9 - 7;
  EXPECT_EQ(c_alpha(), 2);

  EXPECT_THROW(c_alpha.set(-999999999999999);, Ex);  // Exception Tests
  EXPECT_NO_THROW(Coordinate c = 3);
}








//


//  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//  |=======================================================|
//  |===========( COMPARISON & EQUALITY TESTING )===========|
//  |=======================================================|
//  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// TODO: Write test fixture for the comparison-equality tests

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
Coordinate c2048 = 2048;
Coordinate c4096 = 4096;
/*

























*==========================================================*
NOTE: The Coordinate Comparison Operator tests below use a
pair of characters as their method for communicating which
operators are being tested in each test.

If you look at the first test under this comment the name is
'equality_operator_CC' which means that the test is testing
the overloaded equality operator for comparing Coordinate
against Coordinate, hence the 'CC' at the end.

    * CC = Coordinate (operator) Coordinate
    * CI = Coordinate (operator) Integral
    * IC = Integral (operator) Coordinate

The readme file documents and defines the `<Integral>` type.
@SEE -> README.md for more information.
*==========================================================*



------------------------------------------------------------
* COMPARISON: Coordinate | Coordinate
------------------------------------------------------------     */
TEST(CoordinateComparison, equality_operator_CC)
{
  // EQUALITY
  EXPECT_EQ(c00, c00);
  EXPECT_EQ(c01, Coordinate(1));
  EXPECT_TRUE(c08 == Coordinate(8));
  EXPECT_FALSE(c08 == Coordinate(9));
  // !EQUALITY
  EXPECT_NE(c01, Coordinate(2));
  EXPECT_NE(c01, Coordinate(0));
  EXPECT_TRUE(c08 != Coordinate(9));
  EXPECT_FALSE(c08 != Coordinate(8));
}




TEST(CoordinateComparison, greater_operator_CC)
{
  // GREATER
  EXPECT_GT(c01, c00);
  EXPECT_GT(c02, c01);
  EXPECT_GT(c03, c02);
  EXPECT_GT(c04, c03);
  EXPECT_FALSE(c01 > c02);
  EXPECT_FALSE(c02 > c02);
  EXPECT_TRUE(c03 > c02);
  EXPECT_TRUE(Coordinate(111111111112) > Coordinate(111111111111));

  // GREATER or Equal
  EXPECT_GE(c04, c02);
  EXPECT_GE(c04, c04);
  EXPECT_GE(c08, c06);
  EXPECT_GE(c08, c08);
  EXPECT_TRUE(c00 >= Coordinate(0));
  EXPECT_FALSE(c00 >= Coordinate(1));
}




TEST(CoordinateComparison, lesser_operator_CC)
{
  // LESSER
  EXPECT_LT(c01, c02);
  EXPECT_LT(c02, c03);
  EXPECT_LT(c03, c04);
  EXPECT_FALSE(c05 < c05);
  EXPECT_FALSE(c4096 < c2048);
  EXPECT_TRUE(c4096 < Coordinate(5000));

  // LESSER OR EQUAL
  EXPECT_LE(c01, c01);
  EXPECT_LE(c02, c02);
  EXPECT_LE(c02, c03);
  EXPECT_LE(c01, c04);
  EXPECT_FALSE(c01 <= Coordinate(0));
  EXPECT_TRUE(c1024 <= Coordinate(1024));
}
/*











------------------------------------------------------------
* COMPARISON: Integral | Coordinate
------------------------------------------------------------     */
TEST(CoordinateComparison, equality_operator_CI)
{
  // EQUALITY
  EXPECT_EQ(4, c04);
  EXPECT_EQ(8, c08);
  EXPECT_EQ(12, c12);
  EXPECT_TRUE(1 == Coordinate(1));
  EXPECT_FALSE(1 == Coordinate(2));
  EXPECT_FALSE(1 == -1);

  // !EQUALITY
  EXPECT_NE(5, c15);
  EXPECT_NE(10, c05);
  EXPECT_NE(15, c10);
  EXPECT_TRUE(0 != Coordinate(1));
  EXPECT_FALSE(0 != Coordinate(0));
  EXPECT_TRUE(1 != -1);
}




TEST(CoordinateComparison, lesser_operator_CI)
{
  // GREATER
  EXPECT_LT(3, c04);
  EXPECT_LT(5, c08);
  EXPECT_LT(9, c16);
  EXPECT_FALSE(16 < c16);
  EXPECT_FALSE(16 < Coordinate(0));
  EXPECT_TRUE(1234 < c4096);

  // GREATER OR EQUAL
  EXPECT_LE(2, c128);
  EXPECT_LE(2, c256);
  EXPECT_LE(32, c512);
  EXPECT_TRUE(1024 <= c1024);
  EXPECT_FALSE(1024 <= Coordinate(1000));
}




TEST(CoordinateComparison, greater_operator_CI)
{
  // LESSER
  EXPECT_GT(2, c00);
  EXPECT_GT(2, c01);
  EXPECT_FALSE(2 > c02);
  EXPECT_FALSE(2 > c03);
  EXPECT_GT(3, c02);
  EXPECT_FALSE(3 > 3);
  EXPECT_FALSE(3 > Coordinate(4));

  // LESSER OR EQUAL
  EXPECT_FALSE(3 <= c02);
  EXPECT_LE(3, c03);
  EXPECT_LE(3, c04);
  EXPECT_LE(2000, c2048);
  EXPECT_FALSE(2000 <= -13);
}
/*











------------------------------------------------------------
* COMPARISON: Coordinate | Integral
------------------------------------------------------------     */
TEST(Coordinate_Integral_Comparison, equality_operator)
{
  //  EQUALITY(==)
  EXPECT_EQ(c03, 3);
  EXPECT_EQ(c06, 6);
  EXPECT_EQ(c09, 9);
  EXPECT_FALSE(c01 == -1);  // F
  EXPECT_FALSE(c01 == 0);   // F
  EXPECT_TRUE(c01 == 1);    // T

  // !EQUALITY (!=)
  EXPECT_NE(c03, 5);
  EXPECT_NE(c06, 5);
  EXPECT_TRUE(c02 != -2);  // T
  EXPECT_TRUE(c01 != -1);  // T
  EXPECT_FALSE(c00 != 0);  // F
  EXPECT_FALSE(c01 != 1);  // F
  EXPECT_FALSE(c02 != 2);  // F
}




TEST(Coordinate_Integral_Comparison, lesser_operator)
{
  // GREATER
  EXPECT_GT(c03, 0);
  EXPECT_GT(c06, 3);
  EXPECT_GT(c09, 6);
  EXPECT_FALSE(Coordinate(0) < -1);  // F
  EXPECT_FALSE(Coordinate(0) < 0);   // F
  EXPECT_TRUE(Coordinate(0) < 1);    // T
  EXPECT_TRUE(Coordinate(0) < 2);    // T

  // GREATER OR EQUAL
  EXPECT_GE(c03, 3);
  EXPECT_GE(c06, 3);
  EXPECT_GE(c09, 3);
  EXPECT_TRUE(c01 >= -1);  // T
  EXPECT_TRUE(c01 >= 0);   // T
  EXPECT_TRUE(c01 >= 1);   // T
  EXPECT_FALSE(c01 >= 2);  // F
  EXPECT_FALSE(c02 >= 3);  // F
}




TEST(Coordinate_Integral_Comparison, greater_operator)
{
  // LESSER
  EXPECT_LT(c03, 4);
  EXPECT_LT(c06, 7);
  EXPECT_LT(c09, 10);

  // LESSER OR EQUAL
  EXPECT_LE(c10, 12);
  EXPECT_LE(c11, 12);
  EXPECT_LE(c12, 12);
}


////////////////////////////////////////////////////////////
// ARITHMETIC TESTING
////////////////////////////////////////////////////////////

TEST(CoordinateArithmetic, addition)
{
  // TEST ALL THREE OVERLOADS:
  EXPECT_EQ(c01 + c02, c03);
  EXPECT_EQ(c02 + c02, c04);
  EXPECT_EQ(c01 + 2, c03);
  EXPECT_EQ(c02 + 2, c04);
  EXPECT_EQ(1 + c02, c03);
  EXPECT_EQ(2 + c02, c04);

  // Compare different overloaded ops return values
  EXPECT_EQ(5 + c07, c10 + 2);

  // Throws when a negative Coordinate is returned
  EXPECT_THROW(c00 + (-1), Ex);
  EXPECT_THROW((-1) + c00, Ex);

  // Throws only when appropriate to do so
  EXPECT_NO_THROW(c02 + -2);
  EXPECT_NO_THROW(-2 + c02);
}



TEST(CoordinateArithmetic, subtraction)
{
  EXPECT_EQ(c01 - c00, c01);
  EXPECT_EQ(c02 - c01, c01);
  EXPECT_EQ(c03 - 2, c01);
  EXPECT_EQ(c04 - 3, c01);
  EXPECT_EQ(5 - c04, c01);
  EXPECT_EQ(6 - c05, c01);

  EXPECT_THROW(c00 - c01, Ex);
  EXPECT_THROW(c00 - 1, Ex);
  EXPECT_THROW(0 - c02, Ex);
  // EXPECT_THROW(0 - c01, Ex);
}



TEST(CoordinateArithmetic, multiplication)
{
  EXPECT_EQ(c02 * c00, c00);
  EXPECT_EQ(c04 * c02, c08);
  EXPECT_EQ(c08 * c04, c32);
  EXPECT_EQ(c02 * 0, c00);
  EXPECT_EQ(c02 * 1, c02);
  EXPECT_EQ(c02 * 4, c08);
  EXPECT_EQ(8 * c00, c00);
  EXPECT_EQ(8 * c01, c08);
  EXPECT_EQ(8 * c02, c16);

  // THROW ON: 'Returned Negative Coordinate'
  EXPECT_THROW(c01 * (-1), Ex);
  EXPECT_THROW(c02 * -2, Ex);
  EXPECT_THROW((-2) * c01, Ex);
  EXPECT_THROW(-1 * c02, Ex);

  // Don't throw if a negative value is multiplied by zero 0
  EXPECT_NO_THROW(c00 * 0);
  EXPECT_NO_THROW(c00 * -1);
  EXPECT_NO_THROW(0 * c00);
  EXPECT_NO_THROW(-1 * c00);
}





TEST(CoordinateArithmetic, division)
{
  // Standard Division
  // (c/c), (i/c) & (c/i)
  EXPECT_EQ(c16 / c04, c04);
  EXPECT_EQ(c16 / c02, c08);

  //  n/1 = n
  EXPECT_EQ(c02 / c01, c02);
  EXPECT_EQ(4 / c01, c04);
  EXPECT_EQ(c01 / 1, c01);

  // n/0 -> THROW Ex(...)
  EXPECT_THROW(c10 / c00, Ex);
  EXPECT_THROW(0 / c00, Ex);
  EXPECT_THROW(c01 / 0, Ex);

  // 0/n = 0 (NO THROW)
  EXPECT_NO_THROW(c00 / c02);
  EXPECT_EQ(c00 / 2, c00);
  EXPECT_NO_THROW(0 / c02);
  EXPECT_EQ(0 / c02, c00);
  EXPECT_NO_THROW(c00 / 1);
  EXPECT_EQ(c00 / 1, c00);
}



TEST(CoordinateArithmetic, increment_operator)
{
  Coordinate c = 0;
  EXPECT_EQ(++c, c01);
  EXPECT_EQ(++c, c02);
  EXPECT_EQ(++c, c03);
}



TEST(CoordinateArithmetic, decrement_operator)
{
  Coordinate c = 0;

  EXPECT_NO_THROW(--c00);
  EXPECT_EQ(--c, c00);
  EXPECT_EQ(--c, c00);
  EXPECT_EQ(++c, c01);
  EXPECT_EQ(++c, c02);
  EXPECT_EQ(--c, c01);
  EXPECT_EQ(--c, c00);
}
