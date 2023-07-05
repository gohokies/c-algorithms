add_executable(RadixSortBenchmark main.cpp)

target_link_libraries(RadixSortBenchmark sortlib benchmark::benchmark)