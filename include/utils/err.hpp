#pragma once

#include <exception>
#include <format>
#include <iostream>
#include <map>
#include <source_location>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>


namespace Text_Buffer {

enum class ERR_ID
{
    OUT_OF_RANGE        = 1,
    SEG_FAULT_INT_MAX   = 3,
    SEG_FAULT_INT_MIN   = 4,
    DIVISION_BY_ZERO    = 5,
    INVALID_NUMBER_SIGN = 6,
    FILE_SYSTEM_ERROR   = 7,
    FILE_STREAM_ERROR   = 8,
    UNKNOWN             = 99
};





/////////////////////////////////////////////////////////////////
// TO STRING FUNCTIONS
/////////////////////////////////////////////////////////////////
inline std::string to_string(ERR_ID errorId)
{
    // auto n = static_cast<std::underlying_type_t<ErrType>>(errType);
    switch (errorId) {
        case ERR_ID::OUT_OF_RANGE        : return "[OUT_OF_RANGE]";
        case ERR_ID::INVALID_NUMBER_SIGN : return "[INVALID_NUMBER_SIGN]";
        case ERR_ID::SEG_FAULT_INT_MAX   : return "[SEG_FAULT_INT_MAX]";
        case ERR_ID::SEG_FAULT_INT_MIN   : return "[SEG_FAULT_INT_MIN]";
        case ERR_ID::DIVISION_BY_ZERO    : return "[DIVISION_BY_ZERO]";
        case ERR_ID::FILE_SYSTEM_ERROR   : return "[FILE SYSTEM ERROR]";
        case ERR_ID::FILE_STREAM_ERROR   : return "[FILE STREAM ERROR]";
        case ERR_ID::UNKNOWN             : return "[UNKNOWN]";
    };
}



namespace {

    static const std::string clr(int &&code)
    { return std::format("\033[0;38;5;{}m", code); }

    const std::string ESC   = "\033[0m";
    const std::string B     = "\033[1m";
    const std::string UL    = "\033[4m";
    const std::string I     = "\033[3m";
    const std::string DRK_B = "\033[1;38;5;234m";
    const std::string LIGHT = clr(250);
    const std::string DARK  = clr(234);
    const std::string RED   = clr(124);
    const std::string D_RED = clr(52);
    const std::string BLU   = clr(26);  // 25, 26, 32, 33
    const std::string YLW   = clr(58);  // 58, 59, 100, 101
    const std::string GRN   = clr(22);  // 22, 64

}





inline std::vector<std::string> split_on_space(
  const std::string &input,
  size_t             max_length = 80)
{
    std::vector<std::string> result;
    size_t                   start = 0;

    while (start < input.size()) {
        size_t end = start + max_length;

        if (end >= input.size()) {
            result.push_back(input.substr(start));
            break;
        }

        size_t space_pos = input.rfind(' ', end);

        if (space_pos == std::string::npos || space_pos < start) {
            // No space found, or space is before current chunk — hard break
            space_pos = end;
        }

        result.push_back(input.substr(start, space_pos - start));
        start = space_pos + 1;  // Skip the space
    }

    return result;
}





class X_ : public std::exception
{
  public:
    static constexpr const std::string BRK = "\n\t  ";

  private:
    ERR_ID               id;
    std::source_location loc;
    std::string          message;

  public:
    inline X_(
      const ERR_ID        &id,
      const std::string   &msg,
      std::source_location loc = std::source_location::current())
    : id(id)
    , loc(loc)
    , message(formatMesg(msg))
    {}




    inline const char *what() const noexcept override
    {
        std::string msg = std::format("{}", message);
        return message.c_str();
    }




    std::string formatMesg(std::string msg)
    {
        std::string e_id    = to_string(id);
        std::string func    = loc.function_name();
        std::string file    = loc.file_name();
        std::string charNum = std::to_string(loc.column());
        std::string lineNum = std::to_string(loc.line());

        std::string e_code
          = std::to_string(static_cast<std::underlying_type_t<ERR_ID>>(id));

        std::string HORZ
          = "\n*--------------------------------------------------"
            "--------------------------------------------------*\n";

        // FORMATTING (if you study the format calls you can make out the pattern)
        HORZ    = std::format("\n\n\n{}{}{}\n\n", DARK, HORZ, ESC);
        e_id    = std::format("\n\t{}— Error Id: {}{}{}", DARK, DRK_B, e_id, ESC);
        e_code  = std::format("\n\t{}\t | Code: E-{}{}", DARK, e_code, ESC);
        file    = std::format("\n\t{}— Occurred in: {}\"{}\"{}", DARK, I, file, ESC);
        lineNum = std::format("\n\t{}\t| Line #{}{}", DARK, lineNum, ESC);
        charNum = std::format("\n\t{}\t| Col #{}{}", DARK, charNum, ESC);
        func    = std::format("\n\t{}— Thrown By: {}'{}'{}", DRK_B, BLU, func, ESC);

        std::vector<std::string> msgLns = split_on_space("THE CAUSE: " + msg);

        msg.clear();

        for (auto line : msgLns) {
            msg += std::format("\n\t\t{}|  {}{}", D_RED, line, ESC);
        }

        // |  Coordinate subtraction operator ('-') attempted to perform
        return std::format(
          "\n{}\n"
          "\n!ERROR: Execution terminated prematurely due to an unexpected error.\n"
          "{}"  // Error Id
          "{}"  // Error Code
          "\n"
          "{}"  // File where error occurred
          "{}"  // Char Num
          "{}"  // Line Num
          "\n"
          "{}"  // Throwing Function
          "{}"  // Message
          "\n"
          "\n{}",
          HORZ,
          e_id,
          e_code,
          file,
          charNum,
          lineNum,
          func,
          msg,
          HORZ);
    }
};


template <typename T>
concept Integral = std::integral<T>;

struct GenErr
{
    /****************************************************************
     * @private
     * Coordinate Negative Operation Exception
     * @brief Generates an exception that's specifically for the
     * Coordinate class's operators. The returned exception should be
     * thrown whenever a Coordinate's operator preforms an operation
     * that would result in a negative value.
     * @param oper The operator involved in the operation.
     * @param lhs Left-hand side value.
     * @param rhs Right-hand side value.
     * @returns Ex object for illegal negative operation.
     ****************************************************************/
    template <Integral T>
    inline static X_ coord_op_neg(const std::string &oper, T lhs, T rhs) noexcept
    {
        std::string msg = std::format(
          "ILLEGAL OPERATION:  '{} {} {}'  (one of the values is a Coordinate). The "
          "operation is illegal because it results in a negative value; because "
          "Coordinates have an unsigned internal value, the cannot be assigned a value"
          "that is less than 0 (zero).",
          lhs,
          oper,
          rhs);

        return X_(ERR_ID::INVALID_NUMBER_SIGN, msg);
    }



    /**
     * @private
     * Division by Zero Exception
     * @brief Generate an exception for division by zero errors.
     * @returns Ex object for division by zero error.
     * */
    inline static X_ division_by_zero() noexcept
    {
        std::string msg = std::format("Attempted to divide a value by zero");
        return X_(ERR_ID::DIVISION_BY_ZERO, msg);
    }
};

}
