#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"

template<typename T>
static void BM_StdSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        std::sort(v.begin(), v.end());
    }
}

template<typename T>
static void BM_StdStableSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        std::stable_sort(v.begin(), v.end());
    }
}

static void BM_StdSort_UInt32(benchmark::State& state){ BM_StdSort<uint32_t>(state); }
static void BM_StdSort_Int32(benchmark::State& state){ BM_StdSort<int32_t>(state); }
static void BM_StdSort_UInt64(benchmark::State& state){ BM_StdSort<uint64_t>(state); }
static void BM_StdSort_Int64(benchmark::State& state){ BM_StdSort<int64_t>(state); }
static void BM_StdSort_Float(benchmark::State& state){ BM_StdSort<float>(state); }
static void BM_StdSort_Double(benchmark::State& state){ BM_StdSort<double>(state); }

static void BM_StdStableSort_UInt32(benchmark::State& state){ BM_StdStableSort<uint32_t>(state); }
static void BM_StdStableSort_Int32(benchmark::State& state){ BM_StdStableSort<int32_t>(state); }
static void BM_StdStableSort_UInt64(benchmark::State& state){ BM_StdStableSort<uint64_t>(state); }
static void BM_StdStableSort_Int64(benchmark::State& state){ BM_StdStableSort<int64_t>(state); }
static void BM_StdStableSort_Float(benchmark::State& state){ BM_StdStableSort<float>(state); }
static void BM_StdStableSort_Double(benchmark::State& state){ BM_StdStableSort<double>(state); }

// Run the benchmark
BENCHMARK(BM_StdSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdSort_Int64)
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

BENCHMARK(BM_StdStableSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdStableSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdStableSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdStableSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdStableSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_StdStableSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();