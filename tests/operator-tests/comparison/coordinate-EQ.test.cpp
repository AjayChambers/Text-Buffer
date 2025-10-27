/*******************************************************************************
 * PROJECT:     'TextBuffer'
 * FILEPATH:    'tests/coordinate-operator-EQ.test.cpp'
 * REPOSITORY:  'https://github.com/AjayChambers/TextBuffer'
 * COPYRIGHT:   'GPL-3.0'
 * AUTHOR:      'Andrew Jay Chambers'
 * CONTACT:     'w3dojo@gmail.com'
 * DESCRIPTION:
 *   This file tests that Coordinate instantiated objects have an overloaded
 *   equality operator ('==') that works when used with 'int literals',
 *   'explicit size_t', and other Text::Coordinate objects.
 *
 * NOTE:
 *  The TextBuffer project takes advantage of fonts with ligature
 *  support, as a consequence; comments in the TextBuffer project
 *  are well organized, are easy to read, and can say more while
 *  using less characters than a regular font. Unfortunately this
 *  can occasionally result in comments being less readable for
 *  readers using a regular font. The TextBuffer suggested font
 *  is Fira Code, however, both of the fonts 'Cascadia Code' and
 *  'JetBrains Mono' work perfectly fine too.
 *******************************************************************************/

//==================================================*
//=> TEST |> Coordinate |> Operator |> Equality (==)
//==================================================*

#include "../../test-object/comparison-test-case.hpp"

#include <coordinate.hpp>

#include <gtest/gtest.h>

using namespace Text;
using namespace std;
using namespace TextBufferTesting;


// Google Test Class: TestWithParam Testing Class
class OperatorEq : public ::testing::TestWithParam<ComparisonTestCase>
{};




// TEST DEFINITIONS
TEST_P(OperatorEq, CoordinateVsCoordinate) {
    auto p = GetParam();
    EXPECT_EQ(p.ls == p.rsCoord, p.expectedCoord);
}

TEST_P(OperatorEq, CoordinateVsInt) {
    auto p = GetParam();
    EXPECT_EQ(p.ls == p.rsInt, p.expectedInt);
}

TEST_P(OperatorEq, CoordinateVsSizeT) {
    auto p = GetParam();
    EXPECT_EQ(p.ls == p.rsSize, p.expectedSize);
}





// TEST INSTANCES
INSTANTIATE_TEST_SUITE_P(
 CoordinateOperatorTest,
 OperatorEq,
 ::testing::Values(
  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(2) | ==   | Coord(1)   |  FALSE   |
  // | 2 | Coord(2) | ==   | int(1)     |  FALSE   |
  // | 3 | Coord(2) | ==   | size_t(1)  |  FALSE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(2),
                      Coordinate(1),
                      1,
                      size_t(1),
                      false,
                      false,
                      false },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(2) | ==   | Coord(2)   |   TRUE   |
  // | 2 | Coord(2) | ==   | int(2)     |   TRUE   |
  // | 3 | Coord(2) | ==   | size_t(2)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(2), Coordinate(2), 2, size_t(2), true, true, true },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(1) | ==   | Coord(2)   |  FALSE   |
  // | 2 | Coord(1) | ==   | int(2)     |  FALSE   |
  // | 3 | Coord(1) | ==   | size_t(2)  |  FALSE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(1),
                      Coordinate(2),
                      2,
                      size_t(2),
                      false,
                      false,
                      false },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(5) | ==   | Coord(4)   |  FALSE   |
  // | 2 | Coord(5) | ==   | int(4)     |  FALSE   |
  // | 3 | Coord(5) | ==   | size_t(5)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(5),
                      Coordinate(4),
                      4,
                      size_t(5),
                      false,
                      false,
                      true },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(3) | ==   | Coord(4)   |  FALSE   |
  // | 2 | Coord(3) | ==   | int(4)     |  FALSE   |
  // | 3 | Coord(3) | ==   | size_t(0)  |  FALSE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(3),
                      Coordinate(4),
                      4,
                      size_t(0),
                      false,
                      false,
                      false }));
