find_package(benchmark CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/test/Benchmark/inc)

add_subdirectory(BasicBenchmark)

add_subdirectory(InsertionSortBenchmark)
add_subdirectory(StdSortBenchmark)
add_subdirectory(RadixSortBenchmark)

add_subdirectory(MergeSortCppBenchmark)