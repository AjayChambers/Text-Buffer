# Integrate CTest into the Project
include(CTest)
enable_testing()

# Download & Integrate GTest into the Project
include(gtest)
gtest(https://github.com/google/googletest/archive/refs/heads/main.zip)

# Custom Test Generator Script
include(target_unit_test)



#############################################
## COORDINATE TEST
## EQUALITY OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_EQ
    operator-tests/comparison/coordinate-EQ.test.cpp
    "GTest::gtest_main;text_position"
)


#############################################
## COORDINATE TEST
## GREATER-THAN OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_GT
    operator-tests/comparison/coordinate-GT.test.cpp
    "GTest::gtest_main;text_position"
)



#############################################
## COORDINATE TEST
## GREATER-THAN OR EQUAL-TO OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_GE
    operator-tests/comparison/coordinate-GE.test.cpp
    "GTest::gtest_main;text_position"
)




#############################################
## COORDINATE TEST
## LESS-THAN OR EQUAL-TO OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_LE
    operator-tests/comparison/coordinate-LE.test.cpp
    "GTest::gtest_main;text_position"
)



#############################################
## COORDINATE TEST
## LESS-THAN OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_LT
    operator-tests/comparison/coordinate-LT.test.cpp
    "GTest::gtest_main;text_position"
)



#############################################
## COORDINATE TEST
## NON-EQUALITY OPERATOR
#############################################
target_unit_test(
    test_coordinate_op_NE
    operator-tests/comparison/coordinate-NE.test.cpp
    "GTest::gtest_main;text_position"
)



target_unit_test(
    test_coordinate_ops_arithmetic
    operator-tests/coordinate-arithmetic.test.cpp
    "GTest::gtest_main;text_position"
)




#############################################
# SANDBOX TEST
#############################################
target_unit_test(
    sandbox
    sandbox.test.cpp
    "text_position"
)