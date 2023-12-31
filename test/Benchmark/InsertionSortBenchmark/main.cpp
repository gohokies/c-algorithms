#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"
#include "insertion_sort.hpp"

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
        Test::fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        // Sort
        algorithms::insertion_sort(v.begin(), v.end(), std::less<uint32_t>());
    }
}

// Run the benchmark
BENCHMARK(BM_InsertionSort_UInt32)
    ->Args({2})
    ->Args({3})
    ->Args({4})
    ->Args({5})
    ->Args({6})
    ->Args({7})
    ->Args({8})
    ->Args({1<<4})
    ->Args({1<<6})
    ->Args({1<<8})
    ->Args({1<<12});

BENCHMARK_MAIN();