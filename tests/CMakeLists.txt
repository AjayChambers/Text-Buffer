# Integrate CTest into the Project
include(CTest)
enable_testing()

# Download & Integrate GTest into the Project
include(gtest)
gtest(https://github.com/google/googletest/archive/refs/heads/main.zip)

# Custom Test Generator Script
include(target_unit_test)

target_unit_test(sandbox "sandbox.test.cpp" "text_buffer" )

set(Libs_A)
set(Test_A "CoordinateClassTestSuite")
set(Fpath_A "./coordinate.test.cpp")

set(libs "GTest::gtest_main" "text_buffer")

# TEST A: Coordinate Class Test
target_unit_test(${Test_A} ${Fpath_A} ${libs})