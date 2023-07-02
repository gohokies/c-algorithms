#include <iostream>

#include "mergesort.h"
#include "gtest/gtest.h"
#include "TestHelpers.h"

using namespace Test;

template<typename T>
void CompareMergeSortAndStdSort(std::vector<T> &v1, std::vector<T> &v2, CompareFunc cmp, SwapFunc swap)
{
    struct Comparer
    {
    private:
        CompareFunc _cmp;
    public:
        Comparer(CompareFunc cmp) : _cmp(cmp) {}

        constexpr bool operator()(const T& lhs, const T& rhs) const
        {
            return _cmp(&lhs, &rhs) < 0;
        }
    };

    ASSERT_TRUE(v1.size() == v2.size());

    // Sort one array with std::sort
    std::sort(v1.begin(), v1.end()/*, Comparer(cmp)*/);

    // Sort the other array with Radix sort
    merge_sort(v2.data(), v2.size(), sizeof(T), cmp, swap, nullptr);

    // Verify the two array should be the same
    ASSERT_TRUE(v1 == v2);
}

static int compare_uint32(const void* lhs, const void* rhs)
{
    return Compare<uint32_t>(lhs, rhs);
}

static void swap_uint32(void* lhs, void* rhs, size_t size)
{
    assert(size == sizeof(uint32_t));

    Swap<uint32_t>(lhs, rhs);
}

template<typename T>
void MergeSortTestAndVerify(T delta, size_t N, CompareFunc cmp, SwapFunc swap)
{
    std::vector<T> v1, v2;

    // Fill array
    v1.resize(N);
    fill_random_values<T>(v1.data(), v1.size(), delta);

    // Clone the array
    v2 = v1;

    CompareMergeSortAndStdSort(v1, v2, cmp, swap);
}

TEST(MergeSortTest, MergeSortTest_uint32)
{
    MergeSortTestAndVerify<uint32_t>(0, 24, compare_uint32, swap_uint32);
}