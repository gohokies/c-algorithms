#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "BenchmarkHelpers.h"
#include "mergesort.h"

using namespace Benchmark;
static int compare_uint32(const void* lhs, const void* rhs)
{
    return Benchmark::Compare<uint32_t>(lhs, rhs);
}

static void swap_uint32(void* lhs, void* rhs, size_t size)
{
    assert(size == sizeof(uint32_t));
    Benchmark::Swap<uint32_t>(lhs, rhs);
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
        merge_sort(v.data(), v.size(), sizeof(v[0]), compare_uint32, swap_uint32, buffer.data());
    }
}

// Run the benchmark
BENCHMARK(BM_MergeSortUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();