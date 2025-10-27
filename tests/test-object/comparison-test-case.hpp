#ifndef COMPARISON_TEST_CASE_HPP
#define COMPARISON_TEST_CASE_HPP

#include "../include/coordinate.hpp"


namespace TextBufferTesting {

struct ComparisonTestCase
{
    Text::Coordinate ls;
    Text::Coordinate rsCoord;
    int              rsInt;
    size_t           rsSize;
    bool             expectedCoord;
    bool             expectedInt;
    bool             expectedSize;
};

}

#endif