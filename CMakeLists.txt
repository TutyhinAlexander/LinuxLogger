cmake_minimum_required(VERSION 3.10)
project(Logger VERSION 1.0)

message("C++ compiler: ${CMAKE_CXX_COMPILER}")
message("C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
