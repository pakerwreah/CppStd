cmake_minimum_required(VERSION 3.21)
project(Whatever)

set(CMAKE_CXX_STANDARD 17)

file(GLOB sources "PK/*.h" "PK/*.cpp")

add_executable(whatever main.cpp ${sources})
