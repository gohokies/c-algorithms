#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"
#include "merge_sort.hpp"

template<typename T>
static void BM_MergeSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::merge_sort(v.begin(), v.end());
    }
}

template<typename T>
static void BM_MergeSortInplace(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::merge_sort_inplace(v.begin(), v.end());
    }
}

template<typename T>
static void BM_QuadSort(benchmark::State& state)
{
    std::vector<T> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        Test::fill_random_values<T>(v.data(), v.size(), 0);

        state.ResumeTiming();
        algorithms::quad_sort(v.begin(), v.end());
    }
}

static void BM_MergeSort_UInt32(benchmark::State& state){ BM_MergeSort<uint32_t>(state); }
static void BM_MergeSort_Int32(benchmark::State& state){ BM_MergeSort<int32_t>(state); }
static void BM_MergeSort_UInt64(benchmark::State& state){ BM_MergeSort<uint64_t>(state); }
static void BM_MergeSort_Int64(benchmark::State& state){ BM_MergeSort<int64_t>(state); }
static void BM_MergeSort_Float(benchmark::State& state){ BM_MergeSort<float>(state); }
static void BM_MergeSort_Double(benchmark::State& state){ BM_MergeSort<double>(state); }

static void BM_QuadSort_UInt32(benchmark::State& state){ BM_QuadSort<uint32_t>(state); }
static void BM_QuadSort_Int32(benchmark::State& state){ BM_QuadSort<int32_t>(state); }
static void BM_QuadSort_UInt64(benchmark::State& state){ BM_QuadSort<uint64_t>(state); }
static void BM_QuadSort_Int64(benchmark::State& state){ BM_QuadSort<int64_t>(state); }
static void BM_QuadSort_Float(benchmark::State& state){ BM_QuadSort<float>(state); }
static void BM_QuadSort_Double(benchmark::State& state){ BM_QuadSort<double>(state); }

static void BM_MergeSortInplace_UInt32(benchmark::State& state){ BM_MergeSortInplace<uint32_t>(state); }
static void BM_MergeSortInplace_Int32(benchmark::State& state){ BM_MergeSortInplace<int32_t>(state); }
static void BM_MergeSortInplace_UInt64(benchmark::State& state){ BM_MergeSortInplace<uint64_t>(state); }
static void BM_MergeSortInplace_Int64(benchmark::State& state){ BM_MergeSortInplace<int64_t>(state); }
static void BM_MergeSortInplace_Float(benchmark::State& state){ BM_MergeSortInplace<float>(state); }
static void BM_MergeSortInplace_Double(benchmark::State& state){ BM_MergeSortInplace<double>(state); }

// Run the benchmark
BENCHMARK(BM_MergeSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_MergeSortInplace_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_UInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_Int32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_UInt64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_Int64)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_Float)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK(BM_QuadSort_Double)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();