cmake_minimum_required(VERSION 3.17)
project(proj1)

set(CMAKE_CXX_STANDARD 11)

add_executable(proj1 main.cpp Wordset.cpp convert.cpp)