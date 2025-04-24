cmake_minimum_required(VERSION 3.25)
project(Logger VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(LoggerTest LoggerTest.cpp)

find_package(Logger REQUIRED)

target_link_libraries(LoggerTest PUBLIC DebugTools::Logger)
