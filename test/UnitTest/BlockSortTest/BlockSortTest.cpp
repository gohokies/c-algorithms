#include <iostream>
#include "gtest/gtest.h"

#include "block_sort.hpp"
#include "TestHelpers.h"

using namespace Test;

template<typename T>
void CompareBlockSortAndStdSort(std::vector<T> &v1, std::vector<T> &v2)
{
    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end());

    // Sort the other array with block sort
    algorithms::block_sort(v2.begin(), v2.end(), std::less<T>());

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

template<typename T>
void BlockSortTestAndVerify(T delta, size_t N)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    Test::fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareBlockSortAndStdSort<T>(v1, v2);
}

TEST(BlockSortTest, BlockSortTest_uint32)
{
    BlockSortTestAndVerify<uint32_t>(0, 4096);
}

TEST(BlockSortTest, BlockSortTest_int32)
{
    BlockSortTestAndVerify<int32_t>(RAND_MAX >> 1, 4096);
}

TEST(BlockSortTest, BlockSortTest_uint64)
{
    BlockSortTestAndVerify<uint64_t>(0, 4096);
}

TEST(BlockSortTest, BlockSortTest_int64)
{
    BlockSortTestAndVerify<int64_t>(RAND_MAX >> 1, 4096);
}

TEST(BlockSortTest, BlockSortTest_float)
{
    BlockSortTestAndVerify<float>(RAND_MAX >> 1, 4096);
}

TEST(BlockSortTest, BlockSortTest_double)
{
    BlockSortTestAndVerify<double>(RAND_MAX >> 1, 4096);
}