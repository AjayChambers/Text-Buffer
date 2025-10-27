cmake_minimum_required(VERSION 4.1.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/scripts)

project(Text-Buffer LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(tests)