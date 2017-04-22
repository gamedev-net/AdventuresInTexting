cmake_minimum_required (VERSION 3.1)
project (text-adventure)
add_executable (text-adventure main.cpp)
set_target_properties(text-adventure PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)

