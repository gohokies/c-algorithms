#include <iostream>
#include "gtest/gtest.h"

#include "radix_sort.hpp"
#include "TestHelpers.h"

using namespace Test;

template<typename T>
void CompareRadixSortAndStdSort(std::vector<T> &v1, std::vector<T> &v2)
{
    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end());

    // Sort the other array with Radix sort
    algorithms::radix_sort(v2.begin(), v2.end());

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

template<typename T>
void RadixSortTestAndVerify(T delta, size_t N)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    Test::fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareRadixSortAndStdSort<T>(v1, v2);
}

TEST(RadixSortTest, RadixSortTest_uint32)
{
    RadixSortTestAndVerify<uint32_t>(0, 4096);
}

TEST(RadixSortTest, RadixSortTest_int32)
{
    RadixSortTestAndVerify<int32_t>(RAND_MAX >> 1, 4096);
}

TEST(RadixSortTest, RadixSortTest_uint64)
{
    RadixSortTestAndVerify<uint64_t>(0, 4096);
}

TEST(RadixSortTest, RadixSortTest_int64)
{
    RadixSortTestAndVerify<int64_t>(RAND_MAX >> 1, 4096);
}

TEST(RadixSortTest, RadixSortTest_float)
{
    RadixSortTestAndVerify<float>(static_cast<float>(RAND_MAX >> 1), 4096);
}

TEST(RadixSortTest, RadixSortTest_double)
{
    RadixSortTestAndVerify<double>(static_cast<double>(RAND_MAX >> 1), 4096);
}