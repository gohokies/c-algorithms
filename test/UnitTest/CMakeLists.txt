find_package(GTest CONFIG REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/test/inc)

add_subdirectory(InsertionSortTest)
add_subdirectory(MergeSortTest)
add_subdirectory(RadixSortTest)
add_subdirectory(BlockSortTest)