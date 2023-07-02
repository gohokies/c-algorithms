cmake_minimum_required(VERSION 3.21)

project(algorithms)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(sample)