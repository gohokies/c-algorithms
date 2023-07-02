
add_executable(MergeSortTest MergeSortTest.cpp)

target_link_libraries(MergeSortTest sortlib GTest::gtest GTest::gtest_main)

add_test(MergeSortTest MergeSortTest)
