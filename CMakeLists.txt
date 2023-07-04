cmake_minimum_required(VERSION 3.21)

project(algorithms)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/inc)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(sample)