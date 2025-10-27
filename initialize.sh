#!/bin/bash
###################################################################
## TEXT BUFFER INITIALIZATION SCRIPT                             ##
##                                                               ##
## Initialize TextBuffer project as an x86_64 Linux CMake        ##
## project compiled with CLang and built w/ Ninja.               ##
##                                                               ##
## NOTE: The project can be built and worked on using any        ##
## OS, compiler, or build system. But included in the project    ##
## is this script and a set of VS Code tasks to quickly get      ##
## devs up and running who are planning to work on TextBuffer    ##
## using VS Code, CMake, Linux, CLang & Ninja.                   ##
##                                                               ##
## The toolchain file for the toolchain using the tools/env      ##
## listed above is located at the path mentioned below.          ##
##                                                               ##
## "./cmake/toolchain/clang-linux-x86_64.toolchain.cmake"        ##
###################################################################


export TOOLCHAIN="" # Path for 'clang-linux-x86_64.toolchain.cmake'
export S="" # Source Dir Configuration
export B="" # Build Dir Configuration

set -- \
"-DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE" \
"-DCMAKE_BUILD_TYPE=Debug" \
"-Wdev"

cmake "-G Ninja" "-S $S" "-B $B" "-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_PATH" "$@"