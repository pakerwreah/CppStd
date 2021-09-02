cmake_minimum_required(VERSION 3.21)
project(Whatever)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

file(GLOB sources "PK/*.h" "PK/*.cpp")
file(GLOB tests "tests/*.cpp")

add_executable(whatever ${sources} ${tests})
