/*---------------------------------------------------------------*
 *           GENERAL PUBLIC LICENSE 3.0 (GPL-3.0)
 *
 * TEXT-BUFFER: Library for programming Text processing tools.
 *
 *           COPYRIGHT © 2026 ANDREW JAY CHAMBERS
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, visit the link
 * below.
 *
 * https://www.gnu.org/licenses
 *
 *---------------------------------------------------------------*
 *
 * PROJECT: Text-Buffer
 * FILENAME: 'coordinate.hpp
 * AUTHOR: Andrew Jay Chambers Jr (aka Ajay Chambers)
 * EMAIL: 'w3dojo@gmail.com'
 * REPO: https://www.github.com/AjayChambers/TextBuffer"
 * DESCRIPTION: Coordinate class defines a numeric-like object
 *   that acts as a 1 deviational location for the placement of a
 *   character in some text. When used as a single entity it is
 *   typically used to track a file's line number. When used in a
 *   pair they track a file's row and column.
 *
 * For more information about Text-Buffer, see the README.md
 * file in the project's root directory, and/or visit the
 * Text-Buffer repository at the URL listed under REPO above. If
 * you would like to contact me (the author Ajay) email me at the
 * email address above.
 *---------------------------------------------------------------*/





// --------------------------------------------------------------
// TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!!
// --------------------------------------------------------------
// TODO: Switch to using the generators from the newer exception
// handling system in 'utils/exception.hpp'.
//
// TODO: Confirm overloaded arithmetic operator's display the
// correct error message when throwing an exception.
//
// THOUGHT: If each error is unique it would be easier to test
// that the correct error message is being displayed when thrown.
// Rather than validating each individual exception case, the
// messages can be validated programmatically.
//
// TODO: Add error handling for segmentation faults.
//
// --------------------------------------------------------------
// TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!! TODO!!
// --------------------------------------------------------------






#pragma once
#include "utils/exception.hpp"
#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include "utils/err.hpp"

#include <cstdint>

using namespace Text_Buffer;




namespace Text {

template <typename T>
concept Integral = std::integral<T>;


/**************************************************************
 * Coordinate Class: Defines a numeric-like object that acts
 * as a 1-dimensional location value for character within text.
 * in text. Typically used in a pair for 2-dimensional position
 * tracking in a text file, or some other body of text. Used in
 * such a way is referred to as a Row-Column pair.
 **************************************************************/
class Coordinate
{
  private:
    size_t internal = 0;

  public:
    template <Integral T>
    Coordinate(T num);
    Coordinate(int &&num);
    inline Coordinate() noexcept = default;               /// Default Constructor
    inline Coordinate(Coordinate &) noexcept = default;   /// Copy Constructor
    inline Coordinate(Coordinate &&) noexcept = default;  /// Move Constructor

    // INTERNAL READ ACCESS
    size_t get() const noexcept;
    size_t operator () ();

    // INTERNAL WRITE ACCESS
    template <Integral T>
    void set(const T &num);
    void set(const Coordinate &other);

    template <Integral T>
    Coordinate operator = (const T &number);
    Coordinate operator = (int &&number);
    Coordinate operator = (const Coordinate &number);

    template <Integral T>
    constexpr T convert() const noexcept; /// Type Casting

    template <Integral T>
    operator T() noexcept;

    Coordinate &operator ++ () noexcept;  /// INCREMENT OPERATOR
    Coordinate &operator -- () noexcept;  /// Decrement Operator




    // [C|C] COMPARISON OPERATORS (==, !=, <, >, <=, >=)
    friend bool           operator == (const Coordinate &, const Coordinate &) noexcept;
    friend constexpr auto operator <=> (const Coordinate &, const Coordinate &) noexcept;

    // [C|I] COMPARISON OPERATORS (==, !=, <, >, <=, >=)
    template <Integral T>
    friend bool operator == (const Coordinate &coord, const T &number);

    template <Integral T>
    friend bool operator != (const Coordinate &coord, const T &number);

    template <Integral T>
    friend bool operator > (const Coordinate &coord, const T &number);

    template <Integral T>
    friend bool operator >= (const Coordinate &coord, const T &number);

    template <Integral T>
    friend bool operator < (const Coordinate &coord, const T &number);

    template <Integral T>
    friend bool operator <= (const Coordinate &coord, const T &number);

    // [I|C] COMPARISON OPERATORS ('==', '!=', '<', '>', '<=', '>=')
    template <Integral T>
    friend bool operator == (const T &number, const Coordinate &coord);

    template <Integral T>
    friend bool operator != (const T &number, const Coordinate &coord);

    template <Integral T>
    friend bool operator > (const T &number, const Coordinate &coord);

    template <Integral T>
    friend bool operator >= (const T &number, const Coordinate &coord);

    template <Integral T>
    friend bool operator < (const T &number, const Coordinate &coord);

    template <Integral T>
    friend bool operator <= (const T &number, const Coordinate &coord);




    // [C|C] ARITHMETIC OPERATORS ('+', '-', '*', '/')
    friend Coordinate operator + (const Coordinate &lhs, const Coordinate &rhs) noexcept;
    friend Coordinate operator * (const Coordinate &lhs, const Coordinate &rhs) noexcept;
    friend Coordinate operator - (const Coordinate &lhs, const Coordinate &rhs);
    friend Coordinate operator / (const Coordinate &lhs, const Coordinate &rhs);

    // [C|I] ARITHMETIC OPERATORS ('+', '-', '*', '/')
    template <Integral T>
    friend Coordinate operator + (const Coordinate &coord, T number);

    template <Integral T>
    friend Coordinate operator * (const Coordinate &coord, T number);

    template <Integral T>
    friend Coordinate operator - (const Coordinate &coord, T number);

    template <Integral T>
    friend Coordinate operator / (const Coordinate &coord, T number);

    // [I|C] ARITHMETIC OPERATORS ('+', '-', '*', '/')
    template <Integral T>
    friend Coordinate operator + (T number, const Coordinate &coord);

    template <Integral T>
    friend Coordinate operator * (T number, const Coordinate &coord);

    template <Integral T>
    friend Coordinate operator - (T number, const Coordinate &coord);

    template <Integral T>
    friend Coordinate operator / (T number, const Coordinate &coord);

};  // CLOSE: 'Coordinate Class'






/****************************************************************
 * Construct a Coordinate using any integral like type.
 * @param num <T> integral typed value that is greater than 0.
 * @tparam <T> Positive integer-like type
 * @throws <ERR> When passed a negative value.
 * @see `Integral Concept`.
 ****************************************************************/
template <Integral T>
inline Coordinate::Coordinate(T num)
: internal(num)
{

    if (0 > num) {
        throw generate_negative_number_exception(
          std::format(
            "Attempted to construct a Coordinate using the negative value {}.", num));
    }
}






/****************************************************************
 * Construct a Coordinate from an int literal.
 * @param num <int &&num> rval `int`.
 * @throws when passed a negative value.
 ****************************************************************/
inline Coordinate::Coordinate(int &&num)
: internal(num)
{
    if (0 > num) {
        throw X_(
          ERR_ID::INVALID_NUMBER_SIGN,
          std::format("Attempted to assign the negative value {} to Coordinate", num));
    }
}






/****************************************************************
 * Getter for accessing a Coordinate's internal value.
 * @returns <size_t> The Coordinates numeric value.
 ****************************************************************/
inline size_t Coordinate::get() const noexcept { return internal; }






/****************************************************************
 * Coordinate Parenthesis Operator Member (GETTER)
 *  This operator is a getter that can be used to read the
 *  calling Coordinate's internal value.
 * @overload
 ****************************************************************/
inline size_t Coordinate::operator () () { return get(); }






/****************************************************************
 * @brief Set a Coordinate obj using an integral-like value.
 * @param <const Coordinate &>
 * @throws if the parameter is negative.
 * @returns <Coordinate &> *this
 ****************************************************************/
template <Integral T>
inline void Coordinate::set(const T &num)
{
    if (0 > num) {
        throw X_(
          ERR_ID::INVALID_NUMBER_SIGN,
          std::format("The negative value {} cannot be assigned to a Coordinate", num));
    }

    internal = num;
}






/****************************************************************
 * Copy Mutator: Copys the value of another Coordinate object.
 * @param other Coordinate object to copy from.
 * @returns <Coordinate &> *this
 ****************************************************************/
inline void Coordinate::set(const Coordinate &other) { internal = other.internal; }






/****************************************************************
 * Coordinate Assignment Operator: Assign coordinate a integer.
 * Takes any integer-like type.
 * @param number <T> Integer-like typed number.
 * @returns <Coordinate> new Coordinate object.
 ****************************************************************/
template <Integral T>
inline Coordinate Coordinate::operator = (const T &number)
{
    set(number);
    return Coordinate(number);
}






/****************************************************************
 * Coordinate Assignment Operator: Assign coordinate a integer.
 * Takes any integer-like type.
 * @param other A Literal integer `<int &&>`
 * @returns <Coordinate> new Coordinate object.
 ****************************************************************/
inline Coordinate Coordinate::operator = (int &&number)
{
    set(number);
    return Coordinate(number);
}






/****************************************************************
 * Coordinate Copy Assignment Operator: Copys the value of
 * a Coordinate into another Coordinate.
 * @param other Coordinate that gets copied from.
 * @returns `*(this)` Coordinate that was copied to.
 ****************************************************************/
inline Coordinate Coordinate::operator = (const Coordinate &number)
{
    set(number);
    return *this;
}






/****************************************************************
 * Convert calling Coordinate to type <T>.
 * @tparam An integer-like type to covert the Coordinate to.
 * @returns Internal Coordinate value as type <T>.
 ****************************************************************/
template <Integral T>
inline constexpr T Coordinate::convert() const noexcept
{ return static_cast<T>(internal); }






/****************************************************************
 * Cast/Convert calling Coordinate to type <T>.
 * @tparam An integer-like type to covert the Coordinate to.
 * @returns Internal Coordinate value as type <T>.
 ****************************************************************/
template <Integral T>
inline Coordinate::operator T() noexcept
{ return convert<T>(); }






/*****************************************************************
 * Coordinate Increment Operator
 * @brief Increases the value of the calling Coordinate by 1.
 * @returns Reference to the calling Coordinate after increment.
 ****************************************************************/
inline Coordinate &Coordinate::operator ++ () noexcept
{
    ++internal;
    return *this;
}






/*****************************************************************
 * Coordinate Decrement Operator
 * @brief Reduces the value of the calling Coordinate by 1.
 * @details The decrement operator cannot reduce the Coordinate's
 * value below 0. If such an operation is attempted no action is
 * taken on the Coordinate and it will retain its original value.
 * @returns Reference to the calling Coordinate after decrement.
 ****************************************************************/
inline Coordinate &Coordinate::operator -- () noexcept
{
    if (internal > 0) { --internal; }
    return *this;
}






/****************************************************************
 * @details Overloaded Non-Equality Operator (!=): Tests
 * `Coordinate != Coordinate` for equality. This operator is
 *  is defaulted, and a friend to the Coordinate class.
 * @param lhs Reference to the left Coordinate.
 * @param rhs Reference to the right Coordinate.
 * @returns Returns `true` if the Coordinates are equal.
 ****************************************************************/
inline bool operator == (const Coordinate &, const Coordinate &) noexcept = default;






/****************************************************************
 * @details Overloaded Equality Operator (==): Tests
 * `Coordinate == Integral` for equality.
 * @param lhs <Integral> Reference to leftside numeric value.
 * @param rhs <Coordinate> Reference to rightside Coordinate.
 * @see TextBuffer::Integral to learn how the Coordinate class,
 *   and Text-Buffer project, define the `<Integral>` type.
 * @returns Returns `true` if the Coordinates are NOT equal.
 ****************************************************************/
template <Integral T>  // (CI: ==)
inline bool operator == (const Coordinate &coord, const T &number)
{ return static_cast<T>(coord.internal) == number; }






/****************************************************************
 * @details Overloaded Non-Equality Operator (!=): Tests
 *  `Coordinate != Integral` for NON-equality.
 * @param lhs <Coordinate> Reference to Coordinate on the left
 * @param rhs <Integral> Reference to number on the right,
 * @see TextBuffer::Integral to learn how the Coordinate class,
 *   and Text-Buffer project, define the `<Integral>` type.
 * @returns Returns `true` if the Coordinates are NOT equal.
 ****************************************************************/
template <Integral T>
inline bool operator != (const Coordinate &coord, const T &number)
{ return (static_cast<T>(coord.internal) != number); }






// INTEGRAL == COORDINATE
/****************************************************************
 * @details Overloaded Equality Operator (==): Tests
 * `Integral == Coordinate` for equality.
 * @param lhs <Integral> Reference to leftside numeric value.
 * @param rhs <Coordinate> Reference to rightside coordinate.
 * @see TextBuffer::Integral to learn how the Coordinate class,
 *   and Text-Buffer project, define the `<Integral>` type.
 * @returns Returns `true` if the Coordinates are NOT equal.
 ****************************************************************/
template <Integral T>  // (IC: ==)
inline bool operator == (const T &number, const Coordinate &coord)
{ return (number == static_cast<T>(coord.internal)); }






// INTEGRAL != COORDINATE
/****************************************************************
 * @details Overloaded Non-Equality Operator (!=): Tests
 *  `Integral != Coordinate` for NON-equality.
 * @param lhs <Integral> Reference to number on the left
 * @param rhs <Coordinate> Reference to coordinate on the right,
 * @see TextBuffer::Integral to learn how the Coordinate class,
 *   and Text-Buffer project, define the `<Integral>` type.
 * @returns Returns `true` if the Coordinates are NOT equal.
 ****************************************************************/
template <Integral T>  // (IC: !=)
inline bool operator != (const T &number, const Coordinate &coord)
{ return number != static_cast<T>(coord.internal); }






/****************************************************************
 * Comparison Operator: 'Greater-than'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 ****************************************************************/
template <Integral T>
inline bool operator > (const Coordinate &coord, const T &number)
{ return static_cast<T>(coord.internal) > number; }






/****************************************************************
 * Comparison Operator: 'Greater-than-or-equal-to'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 ****************************************************************/
template <Integral T>
inline bool operator >= (const Coordinate &coord, const T &number)
{ return static_cast<T>(coord.internal) >= number; }






/****************************************************************
 * Comparison Operator: 'Less-than'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 ****************************************************************/
template <Integral T>
inline bool operator < (const Coordinate &coord, const T &number)
{ return static_cast<T>(coord.internal) < number; }






/****************************************************************
 * Comparison Operator: 'Less-than-or-equal-to'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 ****************************************************************/
template <Integral T>
inline bool operator <= (const Coordinate &coord, const T &number)
{ return static_cast<T>(coord.internal) <= number; }






/****************************************************************
 * @details Coordinate 3-Way Comparison Operator (<=>): This
 *   operator is for testing Coordinate vs Coordinate for
 *   strength or weakness. It is a defaulted operator, and is a
 *   friend to the Coordinate class.
 * @param lhs Reference to the left Coordinate.
 * @param rhs Reference to the right Coordinate.
 * @returns <std::strong_ordering> Compiler-deduced comparison
 *   category type. The exact type depends on the members of
 *   Coordinate.
 ****************************************************************/
inline constexpr auto operator <=> (const Coordinate &, const Coordinate &) noexcept
  = default;






template <Integral T>
inline bool operator > (const T &number, const Coordinate &coord)
{ return number > static_cast<T>(coord.internal); }






/**********************************************************
 * Comparison Operator: 'Greater-than-or-equal-to'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 * @returns true if leftside is greater than or equal to
 *   rightside.
 **********************************************************/
template <Integral T>
inline bool operator >= (const T &number, const Coordinate &coord)
{ return number >= static_cast<T>(coord.internal); }






/**********************************************************
 * Comparison Operator: 'Less-than'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 * @returns true if leftside is less than rightside.
 **********************************************************/
template <Integral T>
inline bool operator < (const T &number, const Coordinate &coord)
{ return number < static_cast<T>(coord.internal); }






/**********************************************************
 * Comparison Operator: 'Less-than-or-equal-to'.
 * @tparam <std::integral T>
 * @param num A positive integer.
 * @param num A positive integer.
 * @returns true if leftside is less than or equal to
 *   rightside.
 **********************************************************/
template <Integral T>
inline bool operator <= (const T &number, const Coordinate &coord)
{ return number <= static_cast<T>(coord.internal); }






/****************************************************************
 * Addition operator. Add together two Coordinates.
 * @param lhs Leftside Coordinate
 * @param rhs Rightside Coordinate
 * @returns A new Coordinate that is equal to the sum.
 ****************************************************************/
inline Coordinate operator + (const Coordinate &lhs, const Coordinate &rhs) noexcept
{ return Coordinate(lhs.internal + rhs.internal); }






/****************************************************************
 * Multiplication operator. Multiply two coordinates.
 * @param lhs Leftside Coordinate
 * @param rhs Rightside Coordinate
 * @returns A new Coordinate that is equal to the product.
 ****************************************************************/
inline Coordinate operator * (const Coordinate &lhs, const Coordinate &rhs) noexcept
{ return Coordinate(lhs.internal * rhs.internal); }






/****************************************************************
 * Division operator. Divides left side Coordinate by the
 * rightside Coordinate.s
 * @param lhs Leftside Coordinate
 * @param rhs Rightside Coordinate
 * @returns A new Coordinate that is equal to the difference.
 ****************************************************************/
inline Coordinate operator - (const Coordinate &lhs, const Coordinate &rhs)
{
    if (rhs.internal > lhs.internal) {
        throw GenErr::coord_op_neg("-", lhs.internal, rhs.internal);
    }

    return Coordinate(lhs.internal - rhs.internal);
}






/****************************************************************
 * Division operator. Divides left side Coordinate by the
 * rightside Coordinate.s
 * @param lhs Leftside Coordinate
 * @param rhs Rightside Coordinate
 * @returns A new Coordinate that is equal to the quotient.
 ****************************************************************/
inline Coordinate operator / (const Coordinate &lhs, const Coordinate &rhs)
{
    if (rhs.internal == 0) { throw GenErr::division_by_zero(); }
    return Coordinate(lhs.internal / rhs.internal);
}






/****************************************************************
 * Addition operator. Add together a Coordinate and an integer.
 * @param coord Leftside Coordinate
 * @param number Rightside integer
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the sum.
 ****************************************************************/
template <Integral T>
inline Coordinate operator + (const Coordinate &coord, T number)
{
    const auto COORD = T(coord.internal);
    if (0 > COORD + number) {
        throw generate_negative_number_exception(
          std::format(
            "The operation {} + {} would result in a negative Coordinate value.",
            COORD,
            number));
    }
    return Coordinate(COORD + number);
}






/****************************************************************
 * Multiplication operator. Multiply two coordinates.
 * @param coord Leftside Coordinate
 * @param number Rightside integer
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the product.
 ****************************************************************/
template <Integral T>
inline Coordinate operator * (const Coordinate &coord, T number)
{
    const auto COORD = T(coord.internal);
    if (COORD == 0) { return Coordinate(0); }
    if (0 > number) {
        throw generate_negative_number_exception(
          std::format(
            "The operation {} * {} would result in a negative Coordinate value.",
            COORD,
            number));
    }
    return Coordinate(COORD * number);
}






/****************************************************************
 * Subtraction operator. Subtract an integer from a Coordinate.
 * @param coord Leftside Coordinate
 * @param number Rightside integer
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the difference.
 ****************************************************************/
template <Integral T>
inline Coordinate operator - (const Coordinate &coord, T number)
{
    const auto COORD = T(coord.internal);
    if (0 > COORD - number) {
        throw generate_negative_number_exception(
          std::format(
            "The operation {} - {} would result in a negative Coordinate value.",
            COORD,
            number));
    }
    return Coordinate(COORD - number);
}






/****************************************************************
 * Division operator. Divides a coordinate by an integers
 * @param coord Leftside Coordinate
 * @param number Rightside integer
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the quotient.
 ****************************************************************/
template <Integral T>
inline Coordinate operator / (const Coordinate &coord, T number)
{
    const auto COORD = T(coord.internal);
    if (number == 0) {
        throw generate_negative_number_exception(
          std::format(
            "The operation {} / {} would result in a negative Coordinate value.",
            COORD,
            number));
    }
    if (0 > COORD / number) {
        throw generate_division_by_zero_exception(
          "Division by zero produces a result that cannot be represented because the "
          "result is considered 'NOT REAL'");
    }
    return Coordinate(COORD / number);
}






/****************************************************************
 * Addition operator. Add together an integer and a Coordinate.
 * @param number Leftside integer
 * @param coord Rightside Coordinate
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the sum.
 ****************************************************************/
template <Integral T>
inline Coordinate operator + (T number, const Coordinate &coord)
{
    const auto COORD = T(coord.internal);
    if (0 > number + COORD) { throw GenErr::coord_op_neg("+", number, COORD); }
    return Coordinate(number + COORD);
}






/****************************************************************
 * Multiplication operator. Multiply an integer by a Coordinate.
 * @param number Leftside integer
 * @param coord Rightside Coordinate
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the product.
 ****************************************************************/
template <Integral T>
inline Coordinate operator * (T number, const Coordinate &coord)
{
    const auto COORD = T(coord.internal);
    if (COORD == 0) return Coordinate(0);
    if (0 > number) throw GenErr::coord_op_neg("*", number, COORD);
    return Coordinate(number * COORD);
}






/****************************************************************
 * Subtraction operator. Subtract a Coordinate from an integer.
 * @param number Leftside integer
 * @param coord Rightside Coordinate
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the difference.
 ****************************************************************/
template <Integral T>
inline Coordinate operator - (T number, const Coordinate &coord)
{
    const auto COORD = T(coord.internal);
    if (0 > number - COORD) { throw GenErr::coord_op_neg("-", number, COORD); }
    return Coordinate(number - COORD);
}






/****************************************************************
 * Division operator. Divides an integer by a Coordinate.
 * @param number Leftside integer
 * @param coord Rightside Coordinate
 * @tparam T <Integral T> see README.md to learn about the
 * Coordinate implemented type `Integral`
 * @returns A new Coordinate that is equal to the quotient.
 ****************************************************************/
template <Integral T>
inline Coordinate operator / (T number, const Coordinate &coord)
{
    const auto COORD = T(coord.internal);
    if (COORD == 0) { throw GenErr::division_by_zero(); }
    if (0 > number / COORD) { throw GenErr::coord_op_neg("/", number, COORD); }
    return Coordinate(number / COORD);
}


}  // END NAMESPACE 'TEXT'

#endif