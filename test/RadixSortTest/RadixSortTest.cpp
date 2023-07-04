#include <iostream>
#include "gtest/gtest.h"

#include "radixsort.h"
#include "TestHelpers.h"

using namespace Test;

template<typename T>
void CompareRadixSortAndStdSort(std::vector<T> &v1, std::vector<T> &v2, RadixType type)
{
    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end());

    // Sort the other array with Radix sort
    radix_sort_type_array(v2.data(), v2.size(), sizeof(T), type);

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

template<typename T>
void RadixSortTestAndVerify(T delta, size_t N, RadixType type)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareRadixSortAndStdSort<T>(v1, v2, type);
}

TEST(RadixSortTest, RadixSortTest_uint32)
{
    RadixSortTestAndVerify<uint32_t>(0, 4096, t_uint32);
}

TEST(RadixSortTest, RadixSortTest_int32)
{
    RadixSortTestAndVerify<int32_t>(RAND_MAX >> 1, 4096, t_int32);
}

TEST(RadixSortTest, RadixSortTest_uint64)
{
    RadixSortTestAndVerify<uint64_t>(0, 4096, t_uint64);
}

TEST(RadixSortTest, RadixSortTest_int64)
{
    RadixSortTestAndVerify<int64_t>(RAND_MAX >> 1, 4096, t_int64);
}

TEST(RadixSortTest, RadixSortTest_float)
{
    RadixSortTestAndVerify<float>(RAND_MAX >> 1, 4096, t_float);
}

TEST(RadixSortTest, RadixSortTest_double)
{
    RadixSortTestAndVerify<double>(RAND_MAX >> 1, 4096, t_double);
}