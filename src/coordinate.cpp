#include <coordinate.hpp>

namespace Text
{


/****************************************************************
 * @public
 * @brief Construct a coordinate value using type `int`. The
 * internal value of the object is set to zero (0).
 ****************************************************************/
Coordinate::Coordinate() noexcept
 : internal(0) {}



/****************************************************************
 * @public
 * @brief Construct a coordinate value using type `int`.
 * @param number The number that the Coordinate object's internal
 * value will be set to.
 ****************************************************************/
Coordinate::Coordinate(int number) noexcept
 : internal((number < 0) ? -number : number) {}



/****************************************************************
 * @public
 * @brief Construct a coordinate value using type `size_t`.
 * @param number The number that the Coordinate object's internal
 * value will be set to.
 ****************************************************************/
Coordinate::Coordinate(size_t number) noexcept
 : internal((number < 0) ? -number : number) {}




Coordinate &Coordinate::operator = (int number) noexcept {
    this->internal = (number < 0) ? -number : number;
    return *this;
}

Coordinate &Coordinate::operator = (size_t number) noexcept {
    this->internal = (number < 0) ? -number : number;
    return *this;
}






/****************************************************************
 * @public
 * @brief Retruns the Coordinate object's internal value.
 * @returns The `size_t` internal value of the coordinate object.
 ****************************************************************/
size_t Coordinate::operator () () const noexcept { return internal; }



/****************************************************************
 * @public
 * @brief Cast/convert the `Coordinate` object to type `size_t`.
 * @returns The `size_t` internal value of the coordinate object.
 ****************************************************************/
Coordinate::operator size_t() const noexcept { return internal; }



/****************************************************************
 * @public
 * @brief Cast/convert the `Coordinate` object to type `int`.
 * @returns The `int` internal value of the coordinate object.
 ****************************************************************/
Coordinate::operator int() const noexcept { return static_cast<int>(internal); }




/****************************************************************
 * @public
 * @brief Increases the internal value of the coordinate object
 * by one (1).
 * @returns *this
 ****************************************************************/
Coordinate &Coordinate::operator ++ () noexcept {
    ++internal;
    return *this;
}



/****************************************************************
 * @public
 * @brief Removes 1 from the internal value of the Coordinate
 * object.
 * @note if decrementing the coordinate object would cause its
 * internal value to be a negative number, the decrementing
 * arithmetic will not be preformed. This is how the operator
 * avoids throwing an exception.
 * @returns *this
 ****************************************************************/
Coordinate &Coordinate::operator -- () noexcept {
    if (internal > 0) --internal;
    return *this;
}





Coordinate operator + (const Coordinate &c1, const Coordinate &c2) {
    return Coordinate(c1.internal + c2.internal);
}

Coordinate operator - (const Coordinate &c1, const Coordinate &c2) {
    return Coordinate(c1.internal - c2.internal);
}

Coordinate operator * (const Coordinate &c1, const Coordinate &c2) {
    return Coordinate(c1.internal * c2.internal);
}

Coordinate operator / (const Coordinate &c1, const Coordinate &c2) {
    return Coordinate(c1.internal / c2.internal);
}

}