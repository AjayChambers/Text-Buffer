#pragma once
#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "utils/ex.hpp"
#include "utils/validate.hpp"

#include <compare>
#include <concepts>
#include <cstddef>

using namespace TextBufferProj;
namespace Text
{



class Coordinate {
   private:
    size_t internal;

   public:
    // Constructors
    Coordinate() noexcept;
    Coordinate(int) noexcept;
    explicit Coordinate(size_t) noexcept;
    inline Coordinate(const Coordinate &) noexcept = default;

    // Assignment Operators
    inline Coordinate &operator = (const Coordinate &) noexcept = default;
    Coordinate        &operator = (int number) noexcept;
    Coordinate        &operator = (size_t number) noexcept;


    // Parentheses Operator
    size_t operator () () const noexcept;

    // Type-Cast Operators
    explicit operator size_t() const noexcept;
             operator int() const noexcept;


    // (In/De)crement Operators
    Coordinate &operator ++ () noexcept;
    Coordinate &operator -- () noexcept;



    /////////////////////////////////////////////////////////////
    // Arithmetic Operators
    /////////////////////////////////////////////////////////////
    friend Coordinate operator + (const Coordinate &c1, const Coordinate &c2);
    friend Coordinate operator - (const Coordinate &c1, const Coordinate &c2);
    friend Coordinate operator * (const Coordinate &c1, const Coordinate &c2);
    friend Coordinate operator / (const Coordinate &c1, const Coordinate &c2);



    template <std::integral T>
    inline friend Coordinate operator + (const Coordinate &ls, T rs) {
        T result = Coordinate(ls.internal + rs);
        if (result < 0)
            throw EX(
            "Coordinate operator '+' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator - (const Coordinate &ls, T rs) {
        T result = Coordinate(ls.internal - rs);
        if (result < 0)
            throw EX(
            "Coordinate operator '-' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator * (const Coordinate &ls, T rs) {
        T result = Coordinate(ls.internal * rs);
        if (result < 0)
            throw EX(
            "Coordinate operator '*' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator / (const Coordinate &ls, T rs) {
        T result = Coordinate(ls.internal / rs);
        if (result < 0)
            throw EX(
            "Coordinate operator '/' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator + (const T ls, Coordinate &rs) {
        T result = Coordinate(ls + rs.internal);
        if (result < 0)
            throw EX(
            "Coordinate operator '+' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator - (const T ls, Coordinate &rs) {
        T result = Coordinate(ls - rs.internal);
        if (result < 0)
            throw EX(
            "Coordinate operator '-' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator * (const T ls, Coordinate &rs) {
        T result = Coordinate(ls * rs.internal);
        if (result < 0)
            throw EX(
            "Coordinate operator '*' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    template <std::integral T>
    inline friend Coordinate operator / (const T ls, Coordinate &rs) {
        T result = Coordinate(ls / rs.internal);
        if (result < 0)
            throw EX(
            "Coordinate operator '/' returned a Coordinate object with an internal "
            "value that was less than 0. Coordinate objects must have a positive "
            "internal value.");

        return Coordinate(result);
    }



    inline friend auto operator <=> (const Coordinate &, const Coordinate &)
    = default;



    template <std::integral T>
    inline friend bool operator == (const Coordinate &lhs, T rhs) noexcept {
        return lhs.internal == static_cast<size_t>(rhs);
    }



    template <std::integral T>
    inline friend auto operator <=> (const Coordinate &lhs, T rhs) noexcept {
        return lhs.internal <=> static_cast<size_t>(rhs);
    }



    template <std::integral T>
    inline friend bool operator == (T lhs, const Coordinate &rhs) noexcept {
        return rhs == lhs;  // reuse
    }



    template <std::integral T>
    inline friend auto operator <=> (T lhs, const Coordinate &rhs) noexcept {
        return static_cast<size_t>(lhs) <=> rhs.internal;
    }
};










}  // namespace Text
#endif