cmake_minimum_required(VERSION 3.21)
project(CppStd)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB sources "src/PK/*.h" "src/PK/*.cpp")
file(GLOB tests "tests/*.h" "tests/*.cpp")

add_executable(cppstd ${sources} ${tests})

# Configure code coverage
include(CodeCoverage.cmake)
target_link_libraries(cppstd coverage_config)
