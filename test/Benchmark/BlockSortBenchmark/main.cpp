#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"
#include "block_sort.hpp"

template<typename T>
static void BM_BlockSort(benchmark::State& state)
{
    std::vector<uint32_t> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::block_sort(v.begin(), v.end(), std::less<T>());
    }
}

static void BM_BlockSort_UInt32(benchmark::State& state){ BM_BlockSort<uint32_t>(state); }
static void BM_BlockSort_Int32(benchmark::State& state){ BM_BlockSort<int32_t>(state); }
static void BM_BlockSort_UInt64(benchmark::State& state){ BM_BlockSort<uint64_t>(state); }
static void BM_BlockSort_Int64(benchmark::State& state){ BM_BlockSort<int64_t>(state); }
static void BM_BlockSort_Float(benchmark::State& state){ BM_BlockSort<float>(state); }
static void BM_BlockSort_Double(benchmark::State& state){ BM_BlockSort<double>(state); }

// Run the benchmark
BENCHMARK(BM_BlockSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_BlockSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_BlockSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_BlockSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_BlockSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_BlockSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();