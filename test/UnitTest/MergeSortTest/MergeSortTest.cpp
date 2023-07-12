#include <stdio.h>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"
#include "merge_sort.hpp"
#include "TestHelpers.h"

using namespace std;
using namespace algorithms;

template<typename T, bool ascend>
void MergeSortTestAndVerify(size_t N, T delta)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    Test::fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    if (ascend)
    {
        // Sort one array with std::sort
        std::sort(v1.begin(), v1.end(), std::less<T>());

        // Sort the other array with insertion sort
        algorithms::merge_sort(v2.begin(), v2.end(), std::less<T>());
    }
    else
    {
        // Sort one array with std::sort in descending order
        std::sort(v1.begin(), v1.end(), std::greater_equal<T>());

        // Sort the other array with insertion sort in descending order
        algorithms::merge_sort(v2.begin(), v2.end(), std::greater_equal<T>());
    }

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

template<typename T, bool ascend>
void MergeSortInplaceTestAndVerify(size_t N, T delta)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    Test::fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    if (ascend)
    {
        // Sort one array with std::sort
        std::sort(v1.begin(), v1.end(), std::less<T>());

        // Sort the other array with insertion sort
        algorithms::merge_sort_inplace(v2.begin(), v2.end(), std::less<T>());
    }
    else
    {
        // Sort one array with std::sort in descending order
        std::sort(v1.begin(), v1.end(), std::greater_equal<T>());

        // Sort the other array with insertion sort in descending order
        algorithms::merge_sort_inplace(v2.begin(), v2.end(), std::greater_equal<T>());
    }

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

//
// MergeSort: Test unsigned integers
//
TEST(MergeSortTest, MergeSortUint32)
{
    MergeSortTestAndVerify<uint32_t, true>(1024, 0);
}

TEST(MergeSortTest, MergeSortUint32InDescendingOrder)
{
    MergeSortTestAndVerify<uint32_t, false>(1024, 0);
}

TEST(MergeSortTest, MergeSortUint64)
{
    MergeSortTestAndVerify<uint64_t, true>(1024, 0);
}

TEST(MergeSortTest, MergeSortUint64InDescendingOrder)
{
    MergeSortTestAndVerify<uint64_t, false>(1024, 0);
}

//
// MergeSort: Test signed integers
//
TEST(MergeSortTest, MergeSortInt32)
{
    MergeSortTestAndVerify<int32_t, true>(1024, RAND_MAX >> 1);
}

TEST(MergeSortTest, MergeSortInt32InDescendingOrder)
{
    MergeSortTestAndVerify<int32_t, false>(1024, RAND_MAX >> 1);
}

TEST(MergeSortTest, MergeSortInt64)
{
    MergeSortTestAndVerify<int64_t, true>(1024, RAND_MAX >> 1);
}

TEST(MergeSortTest, MergeSortInt64InDescendingOrder)
{
    MergeSortTestAndVerify<int64_t, false>(1024, RAND_MAX >> 1);
}

//
// MergeSort: Test floating points
//
TEST(MergeSortTest, MergeSortFloat)
{
    MergeSortTestAndVerify<float, true>(1024, static_cast<float>(RAND_MAX >> 1));
}

TEST(MergeSortTest, MergeSortFloatInDescendingOrder)
{
    MergeSortTestAndVerify<float, false>(1024, static_cast<float>(RAND_MAX >> 1));
}

TEST(MergeSortTest, MergeSortDouble)
{
    MergeSortTestAndVerify<double, true>(1024, static_cast<double>(RAND_MAX >> 1));
}

TEST(MergeSortTest, MergeSortDoubleInDescendingOrder)
{
    MergeSortTestAndVerify<double, false>(1024, static_cast<double>(RAND_MAX >> 1));
}

//
// MergeSortInplace: Test unsigned integers
//
TEST(MergeSortInplaceTest, MergeSortInplaceUint32)
{
    MergeSortInplaceTestAndVerify<uint32_t, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceUint32InDescendingOrder)
{
    MergeSortInplaceTestAndVerify<uint32_t, false>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceUint64)
{
    MergeSortInplaceTestAndVerify<uint64_t, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceUint64InDescendingOrder)
{
    MergeSortInplaceTestAndVerify<uint64_t, false>(1024, 0);
}

//
// MergeSortInplace: Test signed integers
//
TEST(MergeSortInplaceTest, MergeSortInplaceInt32)
{
    MergeSortInplaceTestAndVerify<int32_t, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceInt32InDescendingOrder)
{
    MergeSortInplaceTestAndVerify<int32_t, false>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceInt64)
{
    MergeSortInplaceTestAndVerify<int64_t, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceInt64InDescendingOrder)
{
    MergeSortInplaceTestAndVerify<int64_t, false>(1024, 0);
}

//
// MergeSortInplace: Test floating points
//
TEST(MergeSortInplaceTest, MergeSortInplaceFloat)
{
    MergeSortInplaceTestAndVerify<float, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceFloatInDescendingOrder)
{
    MergeSortInplaceTestAndVerify<float, false>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceDouble)
{
    MergeSortInplaceTestAndVerify<double, true>(1024, 0);
}

TEST(MergeSortInplaceTest, MergeSortInplaceDoubleInDescendingOrder)
{
    MergeSortInplaceTestAndVerify<double, false>(1024, 0);
}