#include <random>
#include <vector>

#include <benchmark/benchmark.h>

#include "TestHelpers.h"
#include "radix_sort.hpp"

template<typename T>
void BM_RadixSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::radix_sort(v.begin(), v.end());
    }
}

static void BM_RadixSortUInt32(benchmark::State& state)
{
    BM_RadixSort<uint32_t>(state);
}

static void BM_RadixSortInt32(benchmark::State& state)
{
    BM_RadixSort<int32_t>(state);
}

static void BM_RadixSortUInt64(benchmark::State& state)
{
    BM_RadixSort<uint64_t>(state);
}

static void BM_RadixSortInt64(benchmark::State& state)
{
    BM_RadixSort<int64_t>(state);
}

static void BM_RadixSortFloat(benchmark::State& state)
{
    BM_RadixSort<float>(state);
}

static void BM_RadixSortDouble(benchmark::State& state)
{
    BM_RadixSort<double>(state);
}

// Run the benchmark
BENCHMARK(BM_RadixSortUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_RadixSortInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_RadixSortUInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_RadixSortInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_RadixSortFloat)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_RadixSortDouble)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();