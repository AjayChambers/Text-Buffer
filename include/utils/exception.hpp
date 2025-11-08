#pragma once

#include <array>
#include <cstring>
#include <format>
#include <iostream>
#include <memory>
#include <source_location>
#include <stdexcept>
#include <string>
#include <vector>


namespace Text_Buffer {



/**************************************************************************
 * @private
 * @brief UNIQUE ERROR IDENTITIES
 **************************************************************************/
enum class ERROR_ID
{
    OUT_OF_RANGE     = 10,
    NEGATIVE_NUMBER  = 11,
    DIVISION_BY_ZERO = 12,
    UNKNOWN          = 99,
};




/**************************************************************************
 * @private
 * @brief Converts ERROR_ID to a string representation of itself.
 * @param id The ERROR_ID to convert.
 * @return A string representation of the ERROR_ID.
 **************************************************************************/
inline std::string to_string(ERROR_ID id)
{
    switch (id) {
        case ERROR_ID::OUT_OF_RANGE     : return "[OUT OF RANGE]";
        case ERROR_ID::NEGATIVE_NUMBER  : return "[INVALID NUMBER SIGN]";
        case ERROR_ID::DIVISION_BY_ZERO : return "[DIVISION BY ZERO]";
        case ERROR_ID::UNKNOWN          : return "[UNKNOWN ERROR]";
    }
}




/***************************************************************************
 * @private
 * @brief Converts ERROR_ID to its underlying integer error code.
 * @param id The ERROR_ID to convert.
 * @return The integer error code corresponding to the ERROR_ID.
 **************************************************************************/
inline int get_error_code(ERROR_ID id)
{
    auto error_code = static_cast<std::underlying_type_t<ERROR_ID>>(id);
    return int(error_code);
}






/*************************************************************************
 * @private
 * @brief Splits a string into a vector of strings based on spaces,
 *   ensuring that each substring does not exceed a specified maximum length.
 * @param input The input string to split.
 * @param max_length The maximum length of each substring (default is 80).
 * @return A vector of substrings.
 ************************************************************************/
inline std::vector<std::string> wrap_text(
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






/*************************************************************************
 * @class X_EXCEPTION_X
 * @brief Custom exception class for handling errors in the Text_Buffer
 *   library. Inherits from std::exception and provides detailed error
 *   messages including source location information.
 ************************************************************************/
class Exception : public std::exception
{
  private:
    using src_loc = std::source_location;

  public:
    const std::string ESC  = "\033[0m";
    const std::string RED  = "\033[38;2;130;45;60m";
    const std::string DARK = "\033[38;2;115;115;115m";

    ERROR_ID    id      = ERROR_ID::UNKNOWN;
    std::string message = "";
    std::string cause   = "";
    std::string fix     = "";

    // Source location details
    std::source_location loc      = std::source_location::current();
    std::string_view     file     = "";
    std::string_view     function = "";
    const size_t         line     = 0;
    const size_t         column   = 0;


  public:
    Exception(
      ERROR_ID             id,
      std::string          message = "",
      std::string          cause   = "",
      std::string          fix     = "",
      std::source_location loc     = std::source_location::current())
    : id(id)
    , message(message)
    , cause(cause)
    , fix(fix)
    , loc(loc)
    , file(loc.file_name())
    , function(loc.function_name())
    , line(loc.line())
    , column(loc.column())
    { this->message = format_error_message(); }




    /*************************************************************************
     * @brief Overrides the what() method from std::exception to provide
     *   a detailed error message.
     * @return A C-style string containing the formatted error message.
     ************************************************************************/
    const char *what() const noexcept override { return message.c_str(); }





    std::string format_err_id()
    {
        std::string fmt_error_id = format(
          "{}ERROR IDENTITY: {}{} (#{})", RED, to_string(id), ESC, get_error_code(id));
        return fmt_error_id;
    }


    std::string format_location()
    {
        constexpr std::string_view FMT
          = "{}SOURCE LOCATION:{}\n"
            "  {}File:{}     {}\n"
            "  {}Function:{} {}\n"
            "  {}Line:{}     {}\n"
            "  {}Column:{}   {}";

        return std::format(
          FMT,
          RED,
          ESC,
          DARK,
          ESC,
          file,
          DARK,
          ESC,
          function,
          DARK,
          ESC,
          line,
          DARK,
          ESC,
          column);
    }


    std::string format_messages()
    {
        if (cause.length() > 70) {
            std::string formatted_message;
            for (std::string ln : wrap_text(cause, 70)) {
                formatted_message += ("\n  " + ln);
            }
            cause = formatted_message;
        }

        if (fix.length() > 70) {
            std::string formatted_message;
            for (auto ln : wrap_text(fix, 70)) {
                formatted_message += ("\n  " + ln);
            }
            fix = formatted_message;
        }

        if (message.length() > 70) {
            std::string formatted_message;
            for (auto ln : wrap_text(message, 70)) {
                formatted_message += ("\n  " + ln);
            }
            message = formatted_message;
        }

        std::string unified
          = std::format("{}MESSAGE:{} {}{}{}\n\n", DARK, ESC, RED, message, ESC);

        unified += !cause.empty()
                   ? format("{}CAUSE:{} {}\n\n", DARK, ESC, std::string(cause))
                   : "";

        unified += !fix.empty()
                   ? format("{}SUGGESTED FIX:{} {}\n\n", DARK, ESC, std::string(fix))
                   : "";

        return unified;
    }


    /*************************************************************************
     * @private
     * @brief Formats the complete error message including source location.
     * @param id The ERROR_ID of the exception.
     * @param mesg The main error message.
     * @param loc The source location where the error occurred.
     * @return A formatted string containing the complete error message.
     ************************************************************************/
    std::string format_error_message()
    {

        constexpr std::string_view FMT
          = "\n\n\n\n\n\n\n"
            "\n"
            "\nAn unexpected error caused the program to terminate prematurely"
            "\n"
            "\n  * ABOUT: The error was thrown from inside of a Text-Buffer class or"
            "\n   function. Printing Diagnostic Error Report."
            "\n"
            "\n  * Use the diagnostic information provided below to locate & identify"
            "\n  the cause of the error.:"
            "\n"
            "\n  {}"  // ERROR IDENTITY
            "\n"
            "\n  {}"  // LOCATION INFO
            "\n"
            "\n  {}"  // MESSAGES
            "\n"
            "\n"
            "\n--------------------------------------------------------------------------"
            "\n\n";

        return std::format(FMT, format_err_id(), format_location(), format_messages());
    }
};


/*
    ERRORS THAT NEED GENERATORS:
      [#10] - OUT_OF_RANGE
      [#11] - NEGATIVE_NUMBER
      [#12] - DIVISION_BY_ZERO
*/


inline Exception generate_out_of_range_exception(
  const std::string   &message,
  const std::string   &cause = "",
  const std::string   &fix   = "",
  std::source_location loc   = std::source_location::current())
{ return Exception(ERROR_ID::OUT_OF_RANGE, message, cause, fix, loc); }



inline Exception generate_negative_number_exception(
  const std::string &message,
  const std::string &cause = "",
  const std::string &fix
  = "Remove any operations that are resulting in negative values where negative numbers "
    "arn't allowed. Check types, make sure you understand what entities have signed & "
    "unsigned numeric types. Validate any dynamic inputs to ensure they are non-negative "
    "when used where negative numbers are not allowed.",
  std::source_location loc = std::source_location::current())
{ return Exception(ERROR_ID::NEGATIVE_NUMBER, message, cause, fix, loc); }


inline Exception generate_division_by_zero_exception(
  const std::string &message,
  const std::string &cause = "Division by zero is undefined and cannot be performed.",
  const std::string &fix
  = "Remove any division operations where the denominator is zero."
    "and validate any dynamic inputs to ensure they are non-zero before performing "
    "division.",
  std::source_location loc = std::source_location::current())
{ return Exception(ERROR_ID::DIVISION_BY_ZERO, message, cause, fix, loc); }

}  // namespace Text_Buffer
