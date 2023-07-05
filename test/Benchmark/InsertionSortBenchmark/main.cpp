#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"
#include "insertionsort.h"

using namespace Test;

static bool compare_uint32(const void* lhs, const void* rhs)
{
    return *static_cast<const uint32_t*>(lhs) < *static_cast<const uint32_t*>(rhs);
}

static void BM_InsertionSort_UInt32(benchmark::State& state)
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
        insertion_sort(v.data(), v.size(), sizeof(v[0]), compare_uint32);
    }
}

// Run the benchmark
BENCHMARK(BM_InsertionSort_UInt32)
    ->Args({1<<4})
    ->Args({1<<6})
    ->Args({1<<8})
    ->Args({1<<12});

BENCHMARK_MAIN();