#include <iostream>

#include "mergesort.h"
#include "gtest/gtest.h"
#include "TestHelpers.h"

using namespace Test;

typedef int (*Sort)(
    void *base,
    size_t items,
    size_t size,
    CompareFunc compare,
    void* buffer
    );

template<typename T>
void CompareSortAndStdSort(Sort sort, std::vector<T> &v1, std::vector<T> &v2, CompareFunc cmp)
{
    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end(), Comparer<T>(cmp));

    // Sort the other array with Radix sort
    std::vector<T> swapBuffer(v2.size());
    sort(v2.data(), v2.size(), sizeof(T), cmp, swapBuffer.data());

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

template<typename T>
void SortTestAndVerify(Sort sort, T delta, size_t N, CompareFunc cmp)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareSortAndStdSort(sort, v1, v2, cmp);
}

static bool compare_uint32(const void* lhs, const void* rhs)
{
    return Compare<uint32_t>(lhs, rhs);
}

static bool compare_uint32_reverse(const void* lhs, const void* rhs)
{
    return Compare<uint32_t>(rhs, lhs);
}

static bool compare_uint64(const void* lhs, const void* rhs)
{
    return Compare<uint64_t>(lhs, rhs);
}

static bool compare_uint64_reverse(const void* lhs, const void* rhs)
{
    return Compare<uint64_t>(rhs, lhs);
}

static bool compare_float(const void* lhs, const void* rhs)
{
    return Compare<float>(lhs, rhs);
}

static bool compare_float_reverse(const void* lhs, const void* rhs)
{
    return Compare<float>(rhs, lhs);
}

/////////////////////////////////////////////////////////////
//  MergeSort Test
/////////////////////////////////////////////////////////////
TEST(MergeSortTest, MergeSortTest_uint32)
{
    SortTestAndVerify<uint32_t>(merge_sort, 0, 4096, compare_uint32);
}

TEST(MergeSortTest, MergeSortTestInDescendOrder_uint32)
{
    SortTestAndVerify<uint32_t>(merge_sort, 0, 4096, compare_uint32_reverse);
}

TEST(MergeSortTest, MergeSortTest_uint64)
{
    SortTestAndVerify<uint64_t>(merge_sort, 0, 4096, compare_uint64);
}

TEST(MergeSortTest, MergeSortTestInDescendOrder_uint64)
{
    SortTestAndVerify<uint64_t>(merge_sort, 0, 4096, compare_uint64_reverse);
}

TEST(MergeSortTest, MergeSortTest_float)
{
    SortTestAndVerify<float>(merge_sort, 0, 4096, compare_float);
}

TEST(MergeSortTest, MergeSortTestInDescendOrder_float)
{
    SortTestAndVerify<float>(merge_sort, 0, 4096, compare_float_reverse);
}

/////////////////////////////////////////////////////////////
//  QuadSort Test
/////////////////////////////////////////////////////////////
TEST(QuadSortTest, QuadSortTest_uint32)
{
    SortTestAndVerify<uint32_t>(quad_sort, 0, 4096, compare_uint32);
}

TEST(QuadSortTest, QuadSortTestInDescendOrder_uint32)
{
    SortTestAndVerify<uint32_t>(quad_sort, 0, 4096, compare_uint32_reverse);
}

TEST(QuadSortTest, QuadSortTest_uint64)
{
    SortTestAndVerify<uint64_t>(quad_sort, 0, 4096, compare_uint64);
}

TEST(QuadSortTest, QuadSortTestInDescendOrder_uint64)
{
    SortTestAndVerify<uint64_t>(quad_sort, 0, 4096, compare_uint64_reverse);
}

TEST(QuadSortTest, QuadSortTest_float)
{
    SortTestAndVerify<float>(quad_sort, 0, 4096, compare_float);
}

TEST(QuadSortTest, QuadSortTestInDescendOrder_float)
{
    SortTestAndVerify<float>(quad_sort, 0, 4096, compare_float_reverse);
}