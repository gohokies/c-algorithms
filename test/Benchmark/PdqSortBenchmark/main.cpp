#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "pdqsort.hpp"
#include "TestHelpers.h"

template<typename T>
static void BM_PdqSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        pdqsort(v.begin(), v.end());
    }
}

static void BM_PdqSort_UInt32(benchmark::State& state){ BM_PdqSort<uint32_t>(state); }
static void BM_PdqSort_Int32(benchmark::State& state){ BM_PdqSort<int32_t>(state); }
static void BM_PdqSort_UInt64(benchmark::State& state){ BM_PdqSort<uint64_t>(state); }
static void BM_PdqSort_Int64(benchmark::State& state){ BM_PdqSort<int64_t>(state); }
static void BM_PdqSort_Float(benchmark::State& state){ BM_PdqSort<float>(state); }
static void BM_PdqSort_Double(benchmark::State& state){ BM_PdqSort<double>(state); }

BENCHMARK(BM_PdqSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_PdqSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_PdqSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_PdqSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_PdqSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_PdqSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();