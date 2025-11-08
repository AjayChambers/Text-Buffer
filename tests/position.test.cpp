#include <text/position.hpp>

#include <gtest/gtest.h>

using namespace Text;
using namespace std;




Position pos_01(1);
Position pos_01_00(1, 0);
Position pos_01_01(1, 1);
Position pos_01_02(1, 2);
Position pos_01_03(1, 3);

Position pos_02(2);
Position pos_02_00(2, 0);
Position pos_02_01(2, 1);
Position pos_02_02(2, 2);
Position pos_02_03(2, 3);

Position pos_03(3);
Position pos_03_00(3, 0);
Position pos_03_01(3, 1);
Position pos_03_02(3, 2);
Position pos_03_03(3, 3);










TEST(PositionClassTestSuite, position_instantiation)
{
    EXPECT_NO_THROW(Position pos);        // NO THROW
    EXPECT_NO_THROW(Position pos(1, 1));  // NO THROW

    // TODO: FIXME
    // EXPECT_THROW(Position pos(-1, -1), X_);  // THROWS X_

    // Position pos;
    EXPECT_EQ(1, 1);
    EXPECT_EQ(2, 2);
}










TEST(PositionClassTestSuite, position_operator_equality)
{
    EXPECT_TRUE(pos_01 == pos_01_01);
    EXPECT_TRUE(pos_02 == pos_02_01);
    EXPECT_TRUE(pos_03 == pos_03_01);

    EXPECT_FALSE(pos_01 == pos_03);
    EXPECT_FALSE(pos_02 == pos_01);
    EXPECT_FALSE(pos_03 == pos_02);
}










TEST(PositionClassTestSuite, position_operator_no_equality)
{
    EXPECT_TRUE(pos_02 != pos_03_00);  // -> T
    EXPECT_TRUE(pos_02 != pos_03_01);  // -> T
    EXPECT_TRUE(pos_02 != pos_03_02);  // -> T

    EXPECT_FALSE(pos_01 != pos_01_01);  // -> F
    EXPECT_FALSE(pos_02 != pos_02_01);  // -> F
    EXPECT_FALSE(pos_03 != pos_03_01);  // -> F
}










TEST(PositionClassTestSuite, position_operator_greater)
{
    EXPECT_TRUE (pos_03_02 > pos_03_01);  // (3, 2) > (3, 1) -> T
    EXPECT_FALSE(pos_03_02 > pos_03_02);  // (3, 2) > (3, 2) -> F
    EXPECT_FALSE(pos_03_02 > pos_03_03);  // (3, 2) > (3, 3) -> F

    EXPECT_FALSE(pos_01_01 > pos_01);     // (1, 1) > (1, 1) -> F
    EXPECT_TRUE (pos_01_02 > pos_01);     // (1, 2) > (1, 1) -> T
    EXPECT_TRUE (pos_01_03 > pos_01);     // (1, 3) > (1, 1) -> T
}










TEST(PositionClassTestSuite, position_operator_greater_or_equal)
{
    EXPECT_TRUE (pos_03_02 >= pos_03_01);  // (3, 2) >= (3, 1) -> T
    EXPECT_TRUE (pos_03_02 >= pos_03_02);  // (3, 2) >= (3, 2) -> F
    EXPECT_FALSE(pos_03_02 >= pos_03_03);  // (3, 2) >= (3, 3) -> F

    EXPECT_TRUE(pos_01_01 >= pos_01);      // (1, 1) >= (1, 1) -> F
    EXPECT_TRUE(pos_01_02 >= pos_01);      // (1, 2) >= (1, 1) -> T
    EXPECT_TRUE(pos_01_03 >= pos_01);      // (1, 3) >= (1, 1) -> T
}










TEST(PositionClassTestSuite, position_operator_lesser)
{
    EXPECT_TRUE (pos_01_00 < pos_01);      // (2, 0) < (1, 1) -> T
    EXPECT_FALSE(pos_01_01 < pos_01);      // (1, 1) < (1, 1) -> F
    EXPECT_FALSE(pos_01_02 < pos_01);      // (1, 2) < (1, 1) -> F

    EXPECT_TRUE (pos_02_00 < pos_02);      // (2, 0) < (2, 1) -> T
    EXPECT_FALSE(pos_02_01 < pos_02);      // (2, 1) < (2, 1) -> F
    EXPECT_FALSE(pos_02_02 < pos_02);      // (2, 2) < (2, 1) -> F

    EXPECT_TRUE (pos_03_00 < pos_03);      // (3, 0) < (3, 1) -> T
    EXPECT_FALSE(pos_03_01 < pos_03);      // (3, 1) < (3, 1) -> F
    EXPECT_FALSE(pos_03_02 < pos_03);      // (3, 2) < (3, 1) -> F
}










TEST(PositionClassTestSuite, position_operator_lesser_or_equal)
{
    EXPECT_TRUE (pos_01_00 <= pos_01);      // (2, 0) <= (1, 1) -> T
    EXPECT_TRUE (pos_01_01 <= pos_01);      // (1, 1) <= (1, 1) -> T
    EXPECT_FALSE(pos_01_02 <= pos_01);      // (1, 2) <= (1, 1) -> F

    EXPECT_TRUE (pos_02_00 <= pos_02);      // (2, 0) <= (2, 1) -> T
    EXPECT_TRUE (pos_02_01 <= pos_02);      // (2, 1) <= (2, 1) -> T
    EXPECT_FALSE(pos_02_02 <= pos_02);      // (2, 2) <= (2, 1) -> F

    EXPECT_TRUE (pos_03_00 <= pos_03);      // (3, 0) <= (3, 1) -> T
    EXPECT_TRUE (pos_03_01 <= pos_03);      // (3, 1) <= (3, 1) -> T
    EXPECT_FALSE(pos_03_02 <= pos_03);      // (3, 2) <= (3, 1) -> F
}