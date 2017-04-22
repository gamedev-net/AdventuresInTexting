cmake_minimum_required (VERSION 2.6)
project (text-adventure)
add_executable (text-adventure main.cpp)
set_target_properties(text-adventure PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++11)

