add_library(text_buffer STATIC "text-buffer.cpp" "position.cpp")
target_include_directories(
  text_buffer PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/text"
    "${CMAKE_SOURCE_DIR}/include/utils")