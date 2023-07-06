#include <stdio.h>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"
#include "insertion_sort.hpp"
#include "TestHelpers.h"

template<typename T, bool ascend>
void InsertionSortTestAndVerify(size_t N, T delta)
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
        algorithms::insertion_sort(v2.begin(), v2.end(), std::less<T>());
    }
    else
    {
        // Sort one array with std::sort in descending order
        std::sort(v1.begin(), v1.end(), std::greater_equal<T>());

        // Sort the other array with insertion sort in descending order
        algorithms::insertion_sort(v2.begin(), v2.end(), std::greater_equal<T>());
    }

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

//
// Test unsigned integers
//
TEST(InsertionSortTest, InsertionSortUint8)
{
    InsertionSortTestAndVerify<uint8_t, true>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint8InDescendingOrder)
{
    InsertionSortTestAndVerify<uint8_t, false>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint16)
{
    InsertionSortTestAndVerify<uint16_t, true>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint16InDescendingOrder)
{
    InsertionSortTestAndVerify<uint16_t, false>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint32)
{
    InsertionSortTestAndVerify<uint32_t, true>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint32InDescendingOrder)
{
    InsertionSortTestAndVerify<uint32_t, false>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint64)
{
    InsertionSortTestAndVerify<uint64_t, true>(256, 0);
}

TEST(InsertionSortTest, InsertionSortUint64InDescendingOrder)
{
    InsertionSortTestAndVerify<uint64_t, false>(256, 0);
}

//
// Test signed integers
//
TEST(InsertionSortTest, InsertionSortInt32)
{
    InsertionSortTestAndVerify<int32_t, true>(256, RAND_MAX >> 1);
}

TEST(InsertionSortTest, InsertionSortInt32InDescendingOrder)
{
    InsertionSortTestAndVerify<int32_t, false>(256, RAND_MAX >> 1);
}

TEST(InsertionSortTest, InsertionSortInt64)
{
    InsertionSortTestAndVerify<int64_t, true>(256, RAND_MAX >> 1);
}

TEST(InsertionSortTest, InsertionSortInt64InDescendingOrder)
{
    InsertionSortTestAndVerify<int64_t, false>(256, RAND_MAX >> 1);
}

//
// Test floating points
//
TEST(InsertionSortTest, InsertionSortFloat)
{
    InsertionSortTestAndVerify<float, true>(256, static_cast<float>(RAND_MAX >> 1));
}

TEST(InsertionSortTest, InsertionSortFloatInDescendingOrder)
{
    InsertionSortTestAndVerify<float, false>(256, static_cast<float>(RAND_MAX >> 1));
}

TEST(InsertionSortTest, InsertionSortDouble)
{
    InsertionSortTestAndVerify<double, true>(256, static_cast<double>(RAND_MAX >> 1));
}

TEST(InsertionSortTest, InsertionSortDoubleInDescendingOrder)
{
    InsertionSortTestAndVerify<double, false>(256, static_cast<double>(RAND_MAX >> 1));
}
