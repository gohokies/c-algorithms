
add_executable(InsertionSortTest InsertionSortTest.cpp)

target_link_libraries(InsertionSortTest sortlib GTest::gtest GTest::gtest_main)

add_test(InsertionSortTest InsertionSortTest)
