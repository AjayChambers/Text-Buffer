// !IMPORTANT TODO!
// TODO: Confirm overloaded arithmetic operator's display the
// correct error message when throwing an exception.
//
// IDEA: If each error is unique it would be easier to test
// that the correct error message is being displayed when thrown.
// Rather than validating each individual exception case, the
// messages can be validated programmatically.


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
   : internal(num)
  {
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
   : internal(num)
  {
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
  template <Integral T> inline constexpr T convert() const noexcept
  { return static_cast<T>(internal); }


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
  template <Integral T> inline void set(const T &num)
  {
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


  template <Integral T> inline Coordinate operator = (const T &num)
  {
    set(num);
    return Coordinate(num);
  }


  inline Coordinate operator = (const Coordinate &num)
  {
    set(num);
    return *this;
  }


  inline Coordinate operator = (int &&num)
  {
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
  inline friend bool operator == (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) == rhs; }

  template <Integral T>
  inline friend bool operator != (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) != rhs; }


  /**************************************************************
   * Comparison Operator: 'Greater-than'.
   * @tparam <std::integral T>
   * @param num A positive integer.
   * @param num A positive integer.
   **************************************************************/
  template <Integral T>
  inline friend bool operator > (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) > rhs; }

  template <Integral T>
  inline friend bool operator >= (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) >= rhs; }

  template <Integral T>
  inline friend bool operator < (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) < rhs; }

  template <Integral T>
  inline friend bool operator <= (const Coordinate &lhs, const T &rhs)
  { return static_cast<T>(lhs.internal) <= rhs; }




  // ------------------------------------------------------------
  // * COMPARISON OPERATORS:  <Integral> ==to== <Coordinate>
  // ------------------------------------------------------------

  template <Integral T>
  inline friend bool operator == (const T &lhs, const Coordinate &rhs)
  { return lhs == static_cast<T>(rhs.internal); }

  template <Integral T>
  inline friend bool operator != (const T &lhs, const Coordinate &rhs)
  { return lhs != static_cast<T>(rhs.internal); }


  template <Integral T>
  inline friend bool operator > (const T &lhs, const Coordinate &rhs)
  { return lhs > static_cast<T>(rhs.internal); }

  template <Integral T>
  inline friend bool operator >= (const T &lhs, const Coordinate &rhs)
  { return lhs >= static_cast<T>(rhs.internal); }

  template <Integral T>
  inline friend bool operator < (const T &lhs, const Coordinate &rhs)
  { return lhs < static_cast<T>(rhs.internal); }

  template <Integral T>
  inline friend bool operator <= (const T &lhs, const Coordinate &rhs)
  { return lhs <= static_cast<T>(rhs.internal); }








  /**************************************************************
   * Arithmetic Operator (+). Returns the sum of two Coordinates.
   * @param lhs Leftside Coordinate
   * @param rhs Rightside Coordinate
   * @returns Coordinate typed difference.
   **************************************************************/
  inline friend Coordinate operator + (const Coordinate &lhs, const Coordinate &rhs)
  { return Coordinate(lhs.internal + rhs.internal); }



  /**************************************************************
   * Arithmetic Operator (+). Returns the sum of two Coordinates.
   * @tparam <Integral T>
   * @param lhs Leftside type `T` integer.
   * @param rhs Rightside Coordinate.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator + (const T &lhs, const Coordinate &rhs)
  {
    const auto  RHS = T(rhs.internal);
    std::string msg = std::format(
     "Illegal operation: ({} + {}). Coordinates cannot be negative.", lhs, RHS);

    if (lhs < 0 && -lhs > RHS) { throw Ex(E_ID::OUT_OF_RANGE, msg); }

    return Coordinate(RHS + lhs);
  }



  /**************************************************************
   * Arithmetic Operator (+). Returns the sum of two Coordinates.
   * @tparam <Integral T>
   * @param lhs Leftside Coordinate.
   * @param rhs Rightside type `T` integer.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator + (const Coordinate &lhs, const T &rhs)
  {
    const auto  LHS = T(lhs.internal);
    std::string msg = std::format(
     "Illegal operation: ({} + {}). Coordinates cannot be negative.", LHS, rhs);

    if (rhs < 0 && -rhs > LHS) { throw Ex(E_ID::OUT_OF_RANGE, msg); }

    return Coordinate(LHS + rhs);
  }








  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * two Coordinates
   * @param lhs Leftside Coordinate
   * @param rhs Rightside Coordinate
   * @returns Coordinate typed difference.
   **************************************************************/
  inline friend Coordinate operator - (const Coordinate &lhs, const Coordinate &rhs)
  {
    if (lhs.internal < rhs.internal) {
      throw Coordinate_Error.at("Negative_Coordinate");
    }
    return Coordinate(lhs.internal - rhs.internal);
  }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * an integer and a Coordinate.
   * @tparam <Integral T>
   * @param lhs Leftside type `T` integer.
   * @param rhs Rightside Coordinate.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator - (const T &lhs, const Coordinate &rhs)
  {
    const auto RHS = T(rhs.internal);
    if (RHS > lhs) { throw Coordinate_Error.at("Negative_Coordinate"); }
    return Coordinate(lhs - RHS);
  }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * a Coordinate and an integer
   * @tparam <Integral T>
   * @param lhs Leftside Coordinate.
   * @param rhs Rightside type `T` integer.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator - (const Coordinate &lhs, const T &rhs)
  {
    const auto LHS = T(lhs.internal);
    if (LHS < rhs) { throw Coordinate_Error.at("Negative_Coordinate"); }
    return Coordinate(LHS - rhs);
  }








  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * two Coordinates
   * @param lhs Leftside Coordinate
   * @param rhs Rightside Coordinate
   * @returns Coordinate typed difference.
   **************************************************************/
  inline friend Coordinate operator * (const Coordinate &lhs, const Coordinate &rhs)
  { return Coordinate(lhs.internal * rhs.internal); }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * an integer and a Coordinate.
   * @tparam <Integral T>
   * @param lhs Leftside type `T` integer.
   * @param rhs Rightside Coordinate.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator * (const T &lhs, const Coordinate &rhs)
  {
    const auto RHS = T(rhs.internal);

    if (RHS == 0) return Coordinate(0);
    if (-lhs > RHS) { throw Coordinate_Error.at("Negative_Coordinate"); }
    return Coordinate(lhs * RHS);
  }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * a Coordinate and an integer
   * @tparam <Integral T>
   * @param lhs Leftside Coordinate.
   * @param rhs Rightside type `T` integer.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator * (const Coordinate &lhs, const T &rhs)
  {
    const auto LHS = T(lhs.internal);

    if (LHS == 0) { return 0; }
    if (-rhs > LHS) { throw Coordinate_Error.at("Negative_Coordinate"); }
    return Coordinate(LHS * rhs);
  }








  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * two Coordinates
   * @param lhs Leftside Coordinate
   * @param rhs Rightside Coordinate
   * @returns Coordinate typed difference.
   **************************************************************/
  inline friend Coordinate operator / (const Coordinate &lhs, const Coordinate &rhs)
  {
    if (rhs.internal == 0) { throw Coordinate_Error.at("Division_by_Zero"); }
    return Coordinate(lhs.internal / rhs.internal);
  }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * an integer and a Coordinate.
   * @tparam <Integral T>
   * @param lhs Leftside type `T` integer.
   * @param rhs Rightside Coordinate.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator / (const T &lhs, const Coordinate &rhs)
  {
    const auto RHS = T(rhs.internal);

    if (RHS == 0) { throw Coordinate_Error.at("Division_by_Zero"); }
    if (0 > lhs / RHS) { throw Coordinate_Error.at("Negative_Coordinate"); }

    return Coordinate(lhs / RHS);
  }



  /**************************************************************
   * Arithmetic Operator (-). Returns the difference between
   * a Coordinate and an integer
   * @tparam <Integral T>
   * @param lhs Leftside Coordinate.
   * @param rhs Rightside type `T` integer.
   * @returns Coordinate typed difference.
   **************************************************************/
  template <Integral T>
  inline friend Coordinate operator / (const Coordinate &lhs, const T &rhs)
  {
    const auto LHS = T(lhs.internal);

    if (rhs == 0) { throw Coordinate_Error.at("Division_by_Zero"); }
    if (0 > (LHS / rhs)) { throw Coordinate_Error.at("Negative_Coordinate"); }

    return Coordinate(LHS / rhs);
  }



  /**************************************************************
   * @brief Increment the internal value of the Coordinate by 1.
   * @returns <Coordinate> *this
   **************************************************************/
  Coordinate &operator ++ () noexcept
  {
    ++internal;
    return *this;
  }


  /**************************************************************
   * @brief Decrement the internal value of the Coordinate by 1.
   * @returns <Coordinate> *this
   **************************************************************/
  Coordinate &operator -- () noexcept
  {
    if (internal > 0) --internal;
    return *this;
  }
};








}  // namespace




// LHS  RHS
// - / 2


#endif