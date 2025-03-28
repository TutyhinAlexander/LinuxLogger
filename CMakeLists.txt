cmake_minimum_required(VERSION 3.10)
project(LoggerTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(LoggerLib)
add_executable(LoggerTest LoggerTest.cpp)

target_link_libraries(LoggerTest PUBLIC LoggerLib)
target_include_directories(LoggerTest PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/LoggerLib")


