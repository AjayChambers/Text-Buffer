/*******************************************************************************
 * PROJECT:     'TextBuffer'
 * FILEPATH:    'tests/coordinate-operator-GE.test.cpp'
 * REPOSITORY:  'https://github.com/AjayChambers/TextBuffer'
 * COPYRIGHT:   'GPL-3.0'
 * AUTHOR:      'Andrew Jay Chambers'
 * CONTACT:     'w3dojo@gmail.com'
 * DESCRIPTION:
 *   This file tests that Coordinate instantiated objects have an overloaded
 *   greater-than or equal operator ('>=') that works when used with 'int
 *   literals', 'explicit size_t', and other Text::Coordinate objects.
 *******************************************************************************/
#include "../../test-object/comparison-test-case.hpp"

#include <coordinate.hpp>

#include <gtest/gtest.h>

using namespace Text;
using namespace std;
using namespace TextBufferTesting;


// Parameterized fixture for >= operator
class OperatorGE : public ::testing::TestWithParam<ComparisonTestCase>
{};


// Coordinate >= Coordinate
TEST_P(OperatorGE, CoordinateVsCoordinate) {
    auto p = GetParam();
    EXPECT_EQ(p.ls >= p.rsCoord, p.expectedCoord);
}


// Coordinate >= int
TEST_P(OperatorGE, CoordinateVsInt) {
    auto p = GetParam();
    EXPECT_EQ(p.ls >= p.rsInt, p.expectedInt);
}


// Coordinate >= size_t
TEST_P(OperatorGE, CoordinateVsSizeT) {
    auto p = GetParam();
    EXPECT_EQ(p.ls >= p.rsSize, p.expectedSize);
}


INSTANTIATE_TEST_SUITE_P(
 CoordinateOperatorTest,
 OperatorGE,
 ::testing::Values(
  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(2) | >=   | Coord(1)   |   TRUE   |
  // | 2 | Coord(2) | >=   | int(1)     |   TRUE   |
  // | 3 | Coord(2) | >=   | size_t(1)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(2), Coordinate(1), 1, size_t(1), true, true, true },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(2) | >=   | Coord(2)   |   TRUE   |
  // | 2 | Coord(2) | >=   | int(2)     |   TRUE   |
  // | 3 | Coord(2) | >=   | size_t(2)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(2), Coordinate(2), 2, size_t(2), true, true, true },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(1) | >=   | Coord(2)   |  FALSE   |
  // | 2 | Coord(1) | >=   | int(2)     |  FALSE   |
  // | 3 | Coord(1) | >=   | size_t(2)  |  FALSE   |
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
  // | 1 | Coord(5) | >=   | Coord(4)   |   TRUE   |
  // | 2 | Coord(5) | >=   | int(4)     |   TRUE   |
  // | 3 | Coord(5) | >=   | size_t(5)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(5), Coordinate(4), 4, size_t(5), true, true, true },


  // *---------------------------------------------|
  // | # |  LEFT    | OPER |   RIGHT    | EXPECTED |
  // |---|----------|------|------------|----------|
  // | 1 | Coord(3) | >=   | Coord(4)   |  FALSE   |
  // | 2 | Coord(3) | >=   | int(4)     |  FALSE   |
  // | 3 | Coord(3) | >=   | size_t(0)  |   TRUE   |
  // |___|__________|______|____________|__________|
  ComparisonTestCase{ Coordinate(3),
                      Coordinate(4),
                      4,
                      size_t(0),
                      false,
                      false,
                      true }));
