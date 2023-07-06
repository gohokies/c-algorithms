#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"
#include "mergesort.h"

using namespace Test;

static bool compare_uint32(const void* lhs, const void* rhs)
{
    return *static_cast<const uint32_t*>(lhs) < *static_cast<const uint32_t*>(rhs);
}

static void BM_MergeSortUInt32(benchmark::State& state)
{
    std::vector<uint32_t> v;
    std::vector<uint32_t> buffer;

    v.resize(state.range(0));
    buffer.resize(v.size());

    for (auto _ : state)
    {
        state.PauseTiming();
        // Fill array
        fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        // Sort
        //merge_sort(v.data(), v.size(), sizeof(v[0]), compare_uint32, buffer.data());
        merge_sort_uint32(v.data(), v.size(), buffer.data());
    }
}

static void BM_QuadSortUInt32(benchmark::State& state)
{
    std::vector<uint32_t> v;
    std::vector<uint32_t> buffer;

    v.resize(state.range(0));
    buffer.resize(v.size());

    for (auto _ : state)
    {
        state.PauseTiming();
        // Fill array
        fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        // Sort
        quad_sort(v.data(), v.size(), sizeof(v[0]), compare_uint32, buffer.data());
    }
}

// Run the benchmark
BENCHMARK(BM_MergeSortUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSortUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();