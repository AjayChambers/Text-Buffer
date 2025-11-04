/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *|===========================================================|*
 *|  PROJ: 'Text-Buffer'                                      |*
 *|  FILE: 'coordinate.hpp'                                   |*
 *|   DIR: 'include'                                          |*
 *|   LIC: 'GPL-3.0'                                          |*
 *|  REPO: "github.com/AjayChambers/TextBuffer"               |*
 *| EMAIL: 'w3dojo@gmail.com'                                 |*
 *|-----------------------------------------------------------|*
 *| FILE DESCRIPTION:                                         |*
 *|   This header file both declares and defines the          |*
 *|   Coordinate class.                                       |*
 *|===========================================================|*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// [TODO]:
//   Throw unique error objects for each different exception case
//   throughout the class, then test that the specific object is
//   thrown. This will ensure that the message expected for a
//   given error is the one that's displayed.

#pragma once
#include <cstdint>
#ifndef COORDINATE_HPP
#define COORDINATE_HPP




#include "utils/err.hpp"


using namespace Text_Buffer;

namespace Text {

namespace {

  template <typename T>
  concept Integral = std::integral<T>;

}


/****************************************************************
 * @public
 * Coordinate Class
 ****************************************************************/
class Coordinate
{
  size_t internal = 0;  /// @private


 public:
  inline Coordinate() noexcept             = default;  /// Constructor
  inline Coordinate(Coordinate &) noexcept = default;  /// Copy Constructor



  /**************************************************************
   * Construct a Coordinate from an int literal.
   * @param num <int &&num> rval `int`.
   * @throws when passed a negative value.
   **************************************************************/
  inline Coordinate(int &&num)
   : internal(num) {
    if (0 > num) {
      throw Ex(
       E_ID::INVALID_NUMBER_SIGN,
       std::format("Attempted to assign the negative value {} to Coordinate", num));
    }
  }


  /**************************************************************
   * Construct a Coordinate using any integral like type.
   * @param num <T> integral typed value that is greater than 0.
   * @tparam <T> Positive integer-like type
   * @throws <ERR> When passed a negative value.
   * @see `Integral Concept`.
   **************************************************************/
  template <Integral T>
  inline Coordinate(T num)
   : internal(num) {
    if (0 > num) {
      throw Ex(
       E_ID::INVALID_NUMBER_SIGN,
       std::format("Attempted to assign the negative value {} to Coordinate", num));
    }
  }








  // ------------------------------
  // * TYPE CONVERSION
  // ------------------------------

  /**************************************************************
   * Convert Coordinate to an `Integral` type.
   * @tparam <T> Positive integer-like type
   * @returns Coordinate's internal value as type `T`.
   **************************************************************/
  template <Integral T> inline constexpr T convert() const noexcept {
    return static_cast<T>(internal);
  }


  /**************************************************************
   * Convert Coordinate to an `Integral` type.
   * @tparam <T> Positive integer-like type
   * @returns Coordinate's internal value as type `T`.
   **************************************************************/
  template <Integral T> inline operator T() noexcept { return convert<T>(); }








  // ------------------------------
  // * ACCESSORS / PARENTHESIS
  // ------------------------------

  /**************************************************************
   * Accessor: Get the Coordinate's numeric location.
   * @returns <size_t> numeric value
   * @overload
   **************************************************************/
  inline size_t get() { return size_t(internal); }


  /**************************************************************
   * Accessor: Get Coordinate's internal numeric value.
   * @returns <size_t> numeric value
   * @overload
   **************************************************************/
  inline size_t operator () () { return convert<size_t>(); }








  // ---------------------------------------------
  // * MUTATORS / ASSIGNMENT OPERATORS
  // ---------------------------------------------
  /**************************************************************
   * @brief Set a Coordinate obj using an integral-like value.
   * @param <const Coordinate &>
   * @throws if the parameter is negative.
   * @returns <Coordinate &> *this
   **************************************************************/
  template <Integral T> inline void set(const T &num) {
    if (0 > num) {
      throw Ex(
       E_ID::INVALID_NUMBER_SIGN,
       std::format("The negative value {} cannot be assigned to a Coordinate", num));
    }
    internal = num;
  }


  /**************************************************************
   * Copy Mutator: Copys the value of another Coordinate object.
   * @param other Coordinate object to copy from.
   * @returns <Coordinate &> *this
   **************************************************************/
  inline void set(const Coordinate &other) { internal = other.internal; }


  /**************************************************************
   * Mutator: Sets Coordinate value using parenthesis operator
   * @param num A positive integer.
   * @tparam <T> Positive integer-like type
   **************************************************************/
  template <Integral T> inline void operator () (const T &num) { internal = num; }


  template <Integral T> inline Coordinate operator = (const T &num) {
    set(num);
    return Coordinate(num);
  }


  inline Coordinate operator = (const Coordinate &num) {
    set(num);
    return *this;
  }


  inline Coordinate operator = (int &&num) {
    set(num);
    return Coordinate(num);
  }




  // *----------------------------------------------------------*
  // | COMPARISON OPERATORS:  <Coordinate> ==to== <Coordinate>  |
  // *----------------------------------------------------------*

  inline friend bool operator == (const Coordinate &, const Coordinate &)  = default;
  inline friend auto operator <=> (const Coordinate &, const Coordinate &) = default;




  // *----------------------------------------------------------*
  // | COMPARISON OPERATORS:  <Coordinate> ==to== <Integral>    |
  // *----------------------------------------------------------*

  template <Integral T>
  inline friend bool operator == (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) == rhs;
  }

  template <Integral T>
  inline friend bool operator != (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) != rhs;
  }


  /**************************************************************
   * Comparison Operator: 'Greater-than'.
   * @tparam <std::integral T>
   * @param num A positive integer.
   * @param num A positive integer.
   **************************************************************/
  template <Integral T>
  inline friend bool operator > (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) > rhs;
  }

  template <Integral T>
  inline friend bool operator >= (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) >= rhs;
  }

  template <Integral T>
  inline friend bool operator < (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) < rhs;
  }

  template <Integral T>
  inline friend bool operator <= (const Coordinate &lhs, const T &rhs) {
    return static_cast<T>(lhs.internal) <= rhs;
  }




  // ------------------------------------------------------------
  // * COMPARISON OPERATORS:  <Integral> ==to== <Coordinate>
  // ------------------------------------------------------------

  template <Integral T>
  inline friend bool operator == (const T &lhs, const Coordinate &rhs) {
    return lhs == static_cast<T>(rhs.internal);
  }

  template <Integral T>
  inline friend bool operator != (const T &lhs, const Coordinate &rhs) {
    return lhs != static_cast<T>(rhs.internal);
  }


  template <Integral T>
  inline friend bool operator > (const T &lhs, const Coordinate &rhs) {
    return lhs > static_cast<T>(rhs.internal);
  }

  template <Integral T>
  inline friend bool operator >= (const T &lhs, const Coordinate &rhs) {
    return lhs >= static_cast<T>(rhs.internal);
  }

  template <Integral T>
  inline friend bool operator < (const T &lhs, const Coordinate &rhs) {
    return lhs < static_cast<T>(rhs.internal);
  }

  template <Integral T>
  inline friend bool operator <= (const T &lhs, const Coordinate &rhs) {
    return lhs <= static_cast<T>(rhs.internal);
  }








  inline friend Coordinate operator + (
   const Coordinate &lhs,
   const Coordinate &rhs) {
    return Coordinate(lhs.internal + rhs.internal);
  }



  template <Integral T>
  inline friend Coordinate operator + (const T &lhs, const Coordinate &rhs) {
    std::string arg_str
     = std::format("Integer({}) + Coordinate({})", lhs, T(rhs.internal));

    if (lhs < 0 && -lhs > T(rhs.internal))
      throw Ex(
       E_ID::OUT_OF_RANGE,
       std::format("The operation {} created a negative Coordinate.", arg_str));

    return T(rhs.internal) + lhs;
  }



  template <Integral T>
  inline friend Coordinate operator + (const Coordinate &lhs, const T &rhs) {
    return rhs + T(lhs.internal);
  }








  inline friend Coordinate operator - (
   const Coordinate &lhs,
   const Coordinate &rhs) {
    if (rhs > lhs) {
      throw Ex(
       E_ID::INVALID_NUMBER_SIGN,
       "The - operator attempted to assign a negative value "
       "to a Coordinate object.");
    }
    return Coordinate(lhs.internal - rhs.internal);
  }

  inline friend Coordinate operator * (
   const Coordinate &lhs,
   const Coordinate &rhs) {
    return Coordinate(lhs.internal * rhs.internal);
  }

  inline friend Coordinate operator / (
   const Coordinate &lhs,
   const Coordinate &rhs) {
    if (rhs.internal == 0) {
      throw Ex(
       E_ID::DIVISION_BY_ZERO,
       "Attempted to divide a Coordinate by zero. Division by 0 (zero)"
       "is never allowed.");
    }
    return Coordinate(lhs.internal / rhs.internal);
  }








  /**************************************************************
   * @brief Increment the internal value of the Coordinate by 1.
   * @returns <Coordinate> *this
   **************************************************************/
  Coordinate &operator ++ () noexcept {
    ++internal;
    return *this;
  }




  /**************************************************************
   * @brief Decrement the internal value of the Coordinate by 1.
   * @returns <Coordinate> *this
   **************************************************************/
  Coordinate &operator -- () noexcept {
    if (internal > 0) --internal;
    return *this;
  }
};








}  // ns end
#endif
// !EoF