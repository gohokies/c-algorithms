#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"

template<typename T>
static void BM_StdSort(benchmark::State& state)
{
    std::vector<uint32_t> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        std::sort(v.begin(), v.end());
    }
}

static void BM_StdSort_UInt32(benchmark::State& state){ BM_StdSort<uint32_t>(state); }
static void BM_StdSort_UInt64(benchmark::State& state){ BM_StdSort<uint64_t>(state); }
static void BM_StdSort_Float(benchmark::State& state){ BM_StdSort<float>(state); }
static void BM_StdSort_Double(benchmark::State& state){ BM_StdSort<double>(state); }

// Run the benchmark
BENCHMARK(BM_StdSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();