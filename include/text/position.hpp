#pragma once
#ifndef POSITION_HPP
#define POSITION_HPP

#include <text/coordinate.hpp>

#include <concepts>
#include <string>
#include <string_view>
#include <utility>
#include <utils/err.hpp>

namespace Text {


struct Coordinates
{
    const Coordinate row;
    const Coordinate col;
};



class Position
{
    Coordinate row;  /// @private
    Coordinate col;  /// @private

  public:
    Position();
    Position(size_t rowNum);
    Position(size_t rowNum, size_t colNum);
    Position(Position &) noexcept  = default;               /// Copy Ctor
    Position(Position &&) noexcept = default;               /// Move Ctors

    Position &operator = (const Position &)     = default;  /// Copy Assignment Ops
    Position &operator = (Position &&) noexcept = default;  /// Move Assignment Op

    Coordinates getCoordinates() noexcept;
    Coordinate  getRow() noexcept;
    Coordinate  getCol() noexcept;

    void setPosition(size_t rowNum, size_t colNum);
    void setRow(size_t rowNum);
    void setCol(size_t colNum);

    Position &operator ++ () noexcept;
    Position &operator ++ (int) noexcept;
    Position &operator -- () noexcept;
    Position &operator -- (int) noexcept;

    friend bool operator == (const Position &lhs, const Position &rhs) noexcept;
    friend std::strong_ordering operator <=> (const Position &lhs, const Position &rhs)
      noexcept;
};

};

#endif