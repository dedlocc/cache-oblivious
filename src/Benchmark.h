#pragma once

#include <chrono>
#include <functional>
#include <iomanip>

struct Benchmark
{
    std::vector<std::chrono::milliseconds::rep> timings;

    Benchmark(size_t n, const std::function<void(void)> & foo);

    friend std::ostream & operator<<(std::ostream & out, const Benchmark & bm);
};
