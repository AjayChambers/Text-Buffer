#pragma once

#ifndef TEXT_BUFFER_HPP
#define TEXT_BUFFER_HPP

#include <string>
#include <string_view>
// #include


namespace Text {

class Buffer
{
  std::string      internal;
  std::string_view view;

 public:
  Buffer()              = default;
  Buffer(const Buffer&) = default;
  Buffer(const std::string& text);
};

}








#endif