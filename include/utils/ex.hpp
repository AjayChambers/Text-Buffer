#pragma once
#ifndef EX_HPP
#define EX_HPP

#include <cstring>
#include <format>
#include <source_location>
#include <string>

using src_loc = std::source_location;

namespace TextBufferProj {

inline std::string exLb = "\n\t       ";

class EX : public std::exception
{
   private:
    src_loc           loc;
    const std::string cause;
    const std::string mesg;

   public:
    inline EX (const std::string &cause, src_loc loc = src_loc::current())
     : loc (loc)
     , cause (cause)
     , mesg (fmtMesg()) {}

    inline const char *what() const noexcept override { return mesg.c_str(); }


   protected:
    inline static std::string X = "\033[0m";

    inline static auto color = [] (std::string code) -> std::string {
        return format ("\033[0;38;5;{}m", code);
    };

    inline std::string fmtMesg() const {
        using str = std::string;
        const str hr
         = "\n----------------------------------------"
           "----------------------------------------\n";
        const str light = color ("250");
        const str dark  = color ("234");
        const str red   = color ("124");
        const str blu   = color ("23");
        const str row   = std::to_string (loc.line());

        const str col = std::to_string (loc.column());
        str init = "!ERROR: An unexpected error caused the program to terminate.";
        str eLoc = "#" + row + " : #" + col + "";
        str file = loc.file_name();
        str func = loc.function_name();

        init  = std::format ("\n{}{}{}\n", red, init, X);
        file  = std::format ("\n{} * FILE LOC: {}\"{}\"{}", light, dark, file, X);
        func  = std::format ("\n{} * FUNC LOC: {}'{}'{}", light, dark, func, X);
        eLoc  = std::format ("\n{} * LINE:COL: {}{}{}", light, blu, eLoc, X);
        str M = std::format ("\n{} * CAUSE: {}{}{}\n", light, red, cause, X);
        return std::format ("\n{}{}{}{}{}{}{}\n", hr, init, file, func, eLoc, M, hr);
    }
};


}  // Nmsp

#endif