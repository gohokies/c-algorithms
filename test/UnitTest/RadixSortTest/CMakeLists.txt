
add_executable(RadixSortTest RadixSortTest.cpp)

target_link_libraries(RadixSortTest sortlib GTest::gtest GTest::gtest_main)

add_test(RadixSortTest RadixSortTest)
