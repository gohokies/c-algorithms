add_executable(MergeSortBenchmark main.cpp)

target_link_libraries(MergeSortBenchmark sortlib benchmark::benchmark)