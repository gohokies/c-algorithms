#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "BenchmarkHelpers.h"
#include "radixsort.h"

using namespace Benchmark;

template<typename T, RadixType type>
void BM_RadixSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        radix_sort_type_array(v.data(), v.size(), sizeof(T), type);
    }
}

static void BM_RadixSortUInt32(benchmark::State& state)
{
    BM_RadixSort<uint32_t, t_uint32>(state);
}

static void BM_RadixSortInt32(benchmark::State& state)
{
    BM_RadixSort<int32_t, t_int32>(state);
}

static void BM_RadixSortUInt64(benchmark::State& state)
{
    BM_RadixSort<uint64_t, t_uint64>(state);
}

static void BM_RadixSortInt64(benchmark::State& state)
{
    BM_RadixSort<int64_t, t_int64>(state);
}

static void BM_RadixSortFloat(benchmark::State& state)
{
    BM_RadixSort<float, t_float>(state);
}

static void BM_RadixSortDouble(benchmark::State& state)
{
    BM_RadixSort<double, t_double>(state);
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