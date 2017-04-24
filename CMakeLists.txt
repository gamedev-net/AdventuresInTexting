cmake_minimum_required (VERSION 2.6)
project (text-adventure)
add_executable (text-adventure main.cpp Adventure.cpp Entity.cpp Player.cpp Room.cpp string_tools.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

