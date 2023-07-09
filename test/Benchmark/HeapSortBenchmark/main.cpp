#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "heap_sort.hpp"
#include "TestHelpers.h"

template<typename T>
static void BM_HeapSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::heap_sort(v.begin(), v.end());
    }
}

static void BM_HeapSort_UInt32(benchmark::State& state){ BM_HeapSort<uint32_t>(state); }
static void BM_HeapSort_Int32(benchmark::State& state){ BM_HeapSort<int32_t>(state); }
static void BM_HeapSort_UInt64(benchmark::State& state){ BM_HeapSort<uint64_t>(state); }
static void BM_HeapSort_Int64(benchmark::State& state){ BM_HeapSort<int64_t>(state); }
static void BM_HeapSort_Float(benchmark::State& state){ BM_HeapSort<float>(state); }
static void BM_HeapSort_Double(benchmark::State& state){ BM_HeapSort<double>(state); }

BENCHMARK(BM_HeapSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_HeapSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_HeapSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_HeapSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_HeapSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_HeapSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();