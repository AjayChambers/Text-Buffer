#include <text/position.hpp>

#include <compare>
#include <cstddef>




namespace Text {

/**********************************************************************
 * Default Constructor: Initializes Position to (1, 1).
 **********************************************************************/
Position::Position()
{
    row = Coordinate(1);
    col = Coordinate(1);
}






/**********************************************************************
 * Constructor with only row number.
 * @param rowNum The row number of the Position.
 **********************************************************************/
Position::Position(size_t rowNum)
{
    row = Coordinate(rowNum);
    col = Coordinate(1);
}






/**********************************************************************
 * Constructor with row and column numbers.
 * @param rowNum The row number of the Position.
 * @param colNum The column number of the Position.
 **********************************************************************/
Position::Position(size_t rowNum, size_t colNum)
: row(rowNum)
, col(colNum)
{}






/**********************************************************************
 * Get the Coordinates of the Position.
 * @return <Coordinates> An object containing Coordinate objs row & col.
 **********************************************************************/
Coordinates Position::getCoordinates() noexcept { return Coordinates{ row, col }; }






/**********************************************************************
 * Get the row Coordinate of the Position.
 * @return <Text::Coordinate> The row Coordinate of the Position.
 **********************************************************************/
Coordinate Position::getRow() noexcept { return row; }






/**********************************************************************
 * Get the col Coordinate of the Position.
 * @return <Text::Coordinate> The col Coordinate of the Position.
 **********************************************************************/
Coordinate Position::getCol() noexcept { return col; }





/**********************************************************************
 * Set the Position's row and column Coordinates.
 * @param rowNum The new row number to set.
 * @param colNum The new column number to set.
 **********************************************************************/
void Position::setPosition(size_t rowNum, size_t colNum)
{
    row = Coordinate(rowNum);
    col = Coordinate(colNum);
}





/**********************************************************************
 * Set the row Coordinate of the Position.
 * @param rowNum The new row number to set.
 **********************************************************************/
void Position::setRow(size_t rowNum) { row = Coordinate(rowNum); }





/**********************************************************************
 * Set the col Coordinate of the Position.
 * @param colNum The new column number to set.
 **********************************************************************/
void Position::setCol(size_t colNum) { col = Coordinate(colNum); }






/**********************************************************************
 *  Increment the calling Position's column by 1.
 **********************************************************************/
Position &Position::operator ++ () noexcept
{
    ++col;
    return *this;
}






/**********************************************************************
 *  Increment the calling Position's row by 1.
 **********************************************************************/
Position &Position::operator ++ (int) noexcept
{
    ++row;
    return *this;
}






/**********************************************************************
 *  Decrement the calling Position's column by 1.
 **********************************************************************/
Position &Position::operator -- () noexcept
{
    --col;
    return *this;
}






/**********************************************************************
 *  Decrement the calling Position's row by 1.
 **********************************************************************/
Position &Position::operator -- (int) noexcept
{
    --row;
    return *this;
}

bool operator == (const Position &lhs, const Position &rhs) noexcept
{ return (lhs.row == rhs.row) && (lhs.col == rhs.col); }






/****************************************************************
 * @details Overloaded Three-Way Comparison Operator
 *  (`<=>`): Compares two Positions.
 * @param pos Reference to left Position.
 * @param other Reference to right Position.
 * @returns `std::strong_ordering` result of comparison.
 ****************************************************************/
std::strong_ordering operator <=> (const Position &lhs, const Position &rhs) noexcept
{
    constexpr const auto EQUIVALENT = std::strong_ordering::equivalent;
    constexpr const auto LESSER     = std::strong_ordering::less;
    constexpr const auto GREATER    = std::strong_ordering::greater;

    const auto L_row = lhs.row.get();
    const auto R_row = rhs.row.get();
    const auto L_col = lhs.col.get();
    const auto R_col = rhs.col.get();

    // Object greatness can be determined if one row value is
    // greater than the other, however; if the row values are
    // equivalent, then we must compare column values.
    if (L_row > R_row) { return GREATER; }
    if (L_row < R_row) { return LESSER; }

    // If the above conditions returned false, then the next
    // step is to compare column values.
    if (L_col > R_col) { return GREATER; }
    if (L_col < R_col) { return LESSER; }

    // If all four conditions above returned false, then we
    // can conclude that the two objects are equivalent.
    return EQUIVALENT;
}



// <=


}  // close namespace (Text)
