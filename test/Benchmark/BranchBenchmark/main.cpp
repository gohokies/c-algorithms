#include <iostream>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "TestHelpers.h"

static std::vector<int32_t> array;
static std::vector<int32_t> array_sorted;

class DataInit
{
public:
    DataInit()
    {
        // Fill array
        array.resize(1 << 20);
        Test::fill_random_values<int32_t>(array.data(), array.size(), 0);
        array_sorted = array;
        std::sort(array_sorted.begin(), array_sorted.end());
    }
};

DataInit _A;

static void BM_Sum(benchmark::State& state)
{
    for (auto _ : state)
    {
        int sum = 0;
        for(size_t i = 0; i < array.size(); i++)
        {
            benchmark::DoNotOptimize(sum += array[i]);
        }
    }
}

static void BM_Sum_IfLowHalf(benchmark::State& state)
{
    for (auto _ : state)
    {
        int sum = 0;
        for(size_t i = 0; i < array.size(); i++)
        {
            if (array[i] < RAND_MAX / 2) benchmark::DoNotOptimize(sum += array[i]);
        }
    }
}

static void BM_Sum_Sorted_IfLowHalf(benchmark::State& state)
{
    for (auto _ : state)
    {
        int sum = 0;
        for(size_t i = 0; i < array_sorted.size(); i++)
        {
            if (array_sorted[i] < RAND_MAX / 2) benchmark::DoNotOptimize(sum += array_sorted[i]);
        }
    }
}

static void BM_Sum_Branchless(benchmark::State& state)
{
    for (auto _ : state)
    {
        int sum = 0;
        for(size_t i = 0; i < array.size(); i++)
        {
            benchmark::DoNotOptimize(sum += ~(-(array[i] < RAND_MAX / 2)) & array[i]);
        }
    }
}

// Run the benchmark
BENCHMARK(BM_Sum);
BENCHMARK(BM_Sum_IfLowHalf);
BENCHMARK(BM_Sum_Sorted_IfLowHalf);
BENCHMARK(BM_Sum_Branchless);

BENCHMARK_MAIN();