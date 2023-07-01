#include <random>
#include <vector>

#include <benchmark/benchmark.h>

static void BM_StdSortUInt32(benchmark::State& state)
{
    std::vector<uint32_t> v;
    for (auto _ : state)
    {
        state.PauseTiming();

        v.resize(state.range(0));
        std::srand(0);
        for(size_t i = 0; i < v.size(); i++)
        {
            v[i] = static_cast<uint32_t>(std::rand());
        }

        state.ResumeTiming();

        std::sort(v.begin(), v.end());
    }
}

// Run the benchmark
BENCHMARK(BM_StdSortUInt32)->Args({1<<12});

BENCHMARK_MAIN();