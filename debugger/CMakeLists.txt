cmake_minimum_required(VERSION 3.0.2)

project(debugger)

add_compile_options(-std=c++14)

include_directories(ext/libelfin ext/linenoise include)
add_executable(min_gdb src/debugger.cpp ext/linenoise/linenoise.c)




