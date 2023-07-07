
add_executable(BlockSortTest BlockSortTest.cpp)

target_link_libraries(BlockSortTest GTest::gtest GTest::gtest_main)

add_test(BlockSortTest BlockSortTest)
