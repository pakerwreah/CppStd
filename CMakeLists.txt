cmake_minimum_required(VERSION 3.21)
project(Whatever)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB sources "src/PK/*.h" "src/PK/*.cpp")
file(GLOB tests "tests/*.h" "tests/*.cpp")

add_executable(whatever ${sources} ${tests})
