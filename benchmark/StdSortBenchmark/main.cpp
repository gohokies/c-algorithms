#include <random>
#include <vector>

#include <benchmark/benchmark.h>
#include "BenchmarkHelpers.h"

using namespace Benchmark;

static void BM_StdSortUInt32(benchmark::State& state)
{
    std::vector<uint32_t> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        // Fill array
        v.resize(state.range(0));
        fill_random_values<uint32_t>(v.data(), v.size(), 0);

        state.ResumeTiming();
        std::sort(v.begin(), v.end());
    }
}

// Run the benchmark
BENCHMARK(BM_StdSortUInt32)
    ->Args({1<<8})
    ->Args({1<<12})
    ->Args({1<<16})
    ->Args({1<<20});

BENCHMARK_MAIN();