#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include <text/coordinate.hpp>

#include <concepts>
#include <string>
#include <string_view>

namespace Text
{

class Position {
  Coordinate row;
  Coordinate col;

 public:
  Position();

  template <std::unsigned_integral T>
  Position(T rowNumber, T columnNumber)
  : row(rowNumber)
  , col(columnNumber)
  {}
};

};

#endif