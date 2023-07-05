#include <iostream>

#include <benchmark/benchmark.h>

template<typename T>
static void BM_Add(benchmark::State& state)
{
    for (auto _ : state)
    {
        T x = static_cast<T>(0);
        for(size_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = static_cast<T>(i) + static_cast<T>(10));            
        }
    }
}

static void BM_AddUInt32(benchmark::State& state)
{
    BM_Add<uint32_t>(state);
}

static void BM_AddUInt64(benchmark::State& state)
{
    BM_Add<uint64_t>(state);
}

static void BM_AddFloat(benchmark::State& state)
{
    BM_Add<float>(state);
}

static void BM_AddDouble(benchmark::State& state)
{
    BM_Add<double>(state);
}

template<typename T>
static void BM_Subtract(benchmark::State& state)
{
    for (auto _ : state)
    {
        T x = static_cast<T>(0);
        for(size_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = static_cast<T>(i) - static_cast<T>(10));            
        }
    }
}

static void BM_SubtractUInt32(benchmark::State& state)
{
    BM_Subtract<uint32_t>(state);
}

static void BM_SubtractUInt64(benchmark::State& state)
{
    BM_Subtract<uint64_t>(state);
}

static void BM_SubtractFloat(benchmark::State& state)
{
    BM_Subtract<float>(state);
}

static void BM_SubtractDouble(benchmark::State& state)
{
    BM_Subtract<double>(state);
}

template<typename T>
static void BM_Multiply(benchmark::State& state)
{
    for (auto _ : state)
    {
        T x = static_cast<T>(0);
        for(size_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = static_cast<T>(i) * static_cast<T>(10));            
        }
    }
}

static void BM_MultiplyUInt32(benchmark::State& state)
{
    BM_Multiply<uint32_t>(state);
}

static void BM_MultiplyUInt64(benchmark::State& state)
{
    BM_Multiply<uint64_t>(state);
}

static void BM_MultiplyFloat(benchmark::State& state)
{
    BM_Multiply<float>(state);
}

static void BM_MultiplyDouble(benchmark::State& state)
{
    BM_Multiply<double>(state);
}

template<typename T>
static void BM_Divide(benchmark::State& state)
{
    for (auto _ : state)
    {
        T x = static_cast<T>(0);
        for(size_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = static_cast<T>(i) / static_cast<T>(10));            
        }
    }
}

static void BM_DivideUInt32(benchmark::State& state)
{
    BM_Divide<uint32_t>(state);
}

static void BM_DivideUInt64(benchmark::State& state)
{
    BM_Divide<uint64_t>(state);
}

static void BM_DivideFloat(benchmark::State& state)
{
    BM_Divide<float>(state);
}

static void BM_DivideDouble(benchmark::State& state)
{
    BM_Divide<double>(state);
}

static void BM_ShiftUInt32(benchmark::State& state)
{
    for (auto _ : state)
    {
        uint32_t x = 0;
        for(uint32_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = i >> 1);            
        }
    }
}

static void BM_ShiftUInt64(benchmark::State& state)
{
    for (auto _ : state)
    {
        uint64_t x = 0;
        for(uint64_t i = 0; i < 1024 * 1024; i++)
        {
            benchmark::DoNotOptimize(x = i >> 16);            
        }
    }
}

// Run the benchmark
BENCHMARK(BM_AddUInt32);
BENCHMARK(BM_AddUInt64);
BENCHMARK(BM_AddFloat);
BENCHMARK(BM_AddDouble);

BENCHMARK(BM_SubtractUInt32);
BENCHMARK(BM_SubtractUInt64);
BENCHMARK(BM_SubtractFloat);
BENCHMARK(BM_SubtractDouble);

BENCHMARK(BM_MultiplyUInt32);
BENCHMARK(BM_MultiplyUInt64);
BENCHMARK(BM_MultiplyFloat);
BENCHMARK(BM_MultiplyDouble);

BENCHMARK(BM_DivideUInt32);
BENCHMARK(BM_DivideUInt64);
BENCHMARK(BM_DivideFloat);
BENCHMARK(BM_DivideDouble);

BENCHMARK(BM_ShiftUInt32);
BENCHMARK(BM_ShiftUInt64);

BENCHMARK_MAIN();