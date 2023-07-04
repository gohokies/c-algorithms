
#include "gtest/gtest.h"

#include "insertionsort.h"
#include "TestHelpers.h"

#include "sortutils.h"

using namespace Test;

template<typename T>
void CompareInsertionSortAndStdSort(std::vector<T> &v1, std::vector<T> &v2, CompareFunc cmp)
{
    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end(), Comparer<T>(cmp));

    // Sort the other array with Radix sort
    insertion_sort(v2.data(), v2.size(), sizeof(T), cmp);

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

static bool compare_uint32(const void* lhs, const void* rhs)
{
    return Compare<uint32_t>(lhs, rhs);
}

static bool compare_uint32_reverse(const void* lhs, const void* rhs)
{
    return Compare<uint32_t>(rhs, lhs);
}

template<typename T>
void InsertionSortTestAndVerify(T delta, size_t N, CompareFunc cmp)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareInsertionSortAndStdSort(v1, v2, cmp);
}

TEST(InsertionSortTest, InsertionSortTest_uint32)
{
    InsertionSortTestAndVerify<uint32_t>(0, 32, compare_uint32);
}

TEST(InsertionSortTest, InsertionSortTestInDescendOrder_uint32)
{
    InsertionSortTestAndVerify<uint32_t>(0, 32, compare_uint32_reverse);
}