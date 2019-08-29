cmake_minimum_required(VERSION 3.5)
project(gameboy)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wconversion")

add_subdirectory(src)
add_subdirectory(test)