add_library(text_buffer STATIC "text-buffer.cpp")
target_include_directories(
  text_buffer PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/text"
    "${CMAKE_SOURCE_DIR}/include/utils")

add_library(text_position STATIC "position.cpp")
target_include_directories(
  text_position PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/include/text"
  "${CMAKE_SOURCE_DIR}/include/utils")

target_link_libraries(text_buffer PUBLIC text_position)