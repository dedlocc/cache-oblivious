#pragma once

#ifndef CACHE_OBLIVIOUS_BENCHMARK_H
#define CACHE_OBLIVIOUS_BENCHMARK_H

#include <chrono>
#include <functional>
#include <iomanip>

struct Benchmark
{
    std::vector<std::chrono::milliseconds::rep> timings;

    Benchmark(const size_t &, const std::function<void(void)> &);

    friend std::ostream &operator<<(std::ostream &, const Benchmark &);
};

#endif //CACHE_OBLIVIOUS_BENCHMARK_H
