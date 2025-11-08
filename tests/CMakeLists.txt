# Integrate CTest into the Project
include(CTest)
enable_testing()
include(gtest)
gtest(https://github.com/google/googletest/archive/refs/heads/main.zip)

# Custom Test Generator Script
include(target_unit_test)

target_unit_test(
    "CoordinateClassTestSuite"
    "coordinate.test.cpp"
    "GTest::gtest_main;text_buffer")

target_unit_test(
    "PositionClassTestSuite"
    "position.test.cpp"
    "GTest::gtest_main;text_position")

target_unit_test(
    sandbox
    "sandbox.test.cpp"
    "text_buffer;text_position")