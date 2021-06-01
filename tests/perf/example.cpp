#include <benchmark/benchmark.h>
#include <memory>

const int32_t repeatCount = 32;

void BM_rawptr_deference(benchmark::State &state) {
    int *p = new int;
    for (const auto _ : state) {
        // REPEAT(benchmark::DoNotOptimize(*p));
        benchmark::DoNotOptimize(*p);
    }
    delete p;
    state.SetItemsProcessed(repeatCount * state.iterations());
}

void BM_scoped_ptr_deference(benchmark::State &state) {
    std::unique_ptr<int> p(new int);
    for (const auto _ : state) {
        // REPEAT(benchmark::DoNotOptimize(*p));
        benchmark::DoNotOptimize(*p);
    }
    state.SetItemsProcessed(repeatCount * state.iterations());
}

void BM_unique_ptr_deference(benchmark::State &state) {
    std::unique_ptr<int> p(std::make_unique<int>());
    for (const auto _ : state) {
        // REPEAT(benchmark::DoNotOptimize(*p));
        benchmark::DoNotOptimize(*p);
    }
    state.SetItemsProcessed(repeatCount * state.iterations());
}

BENCHMARK(BM_rawptr_deference);
BENCHMARK(BM_scoped_ptr_deference);
BENCHMARK(BM_unique_ptr_deference);
// BENCHMARK_MAIN();
