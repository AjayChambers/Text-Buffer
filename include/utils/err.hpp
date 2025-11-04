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

enum class E_ID
{
  OUT_OF_RANGE        = 1,
  SEG_FAULT_INT_MAX   = 2,
  SEG_FAULT_INT_MIN   = 3,
  DIVISION_BY_ZERO    = 4,
  INVALID_NUMBER_SIGN = 5,
  FILE_SYSTEM_ERROR   = 9,
  FILE_STREAM_ERROR   = 10,
  UNKNOWN             = 99
};





/////////////////////////////////////////////////////////////////
// TO STRING FUNCTIONS
/////////////////////////////////////////////////////////////////
inline std::string to_string(E_ID errorId)
{
  // auto n = static_cast<std::underlying_type_t<ErrType>>(errType);
  switch (errorId) {
    case E_ID::OUT_OF_RANGE        : return "[OUT_OF_RANGE]";
    case E_ID::INVALID_NUMBER_SIGN : return "[INVALID_NUMBER_SIGN]";
    case E_ID::SEG_FAULT_INT_MAX   : return "[SEG_FAULT_INT_MAX]";
    case E_ID::SEG_FAULT_INT_MIN   : return "[SEG_FAULT_INT_MIN]";
    case E_ID::DIVISION_BY_ZERO    : return "[DIVISION_BY_ZERO]";
    case E_ID::FILE_SYSTEM_ERROR   : return "[FILE SYSTEM ERROR]";
    case E_ID::FILE_STREAM_ERROR   : return "[FILE STREAM ERROR]";
    case E_ID::UNKNOWN             : return "[UNKNOWN]";
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





class Ex : public std::exception
{
 public:
  static constexpr const std::string BRK = "\n\t  ";

 private:
  E_ID                 id;
  std::source_location loc;
  std::string          message;

 public:
  inline Ex(
   const E_ID          &id,
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
     = std::to_string(static_cast<std::underlying_type_t<E_ID>>(id));

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


const std::map<const std::string, const Ex> Coordinate_Error{
  { "Negative_Coordinate",
   Ex(E_ID::OUT_OF_RANGE,     "Coordinate cannot be less than 0 (zero).")    },
  { "Division_by_Zero",
   Ex(E_ID::DIVISION_BY_ZERO, "Attempted to divide Coordinate by 0 (zero).") }
};

}
