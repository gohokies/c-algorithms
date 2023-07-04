#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "BenchmarkHelpers.h"
#include "merge_sort.hpp"

using namespace Benchmark;

static bool compare_uint32(const void* lhs, const void* rhs)
{
    return Benchmark::Compare<uint32_t>(lhs, rhs);
}

static void BM_MergeSortCppUInt32(benchmark::State& state)
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
        algorithms::merge_sort(v.begin(), v.end());
    }
}

// Run the benchmark
BENCHMARK(BM_MergeSortCppUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();