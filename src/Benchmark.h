#pragma once

#include <chrono>
#include <functional>
#include <iomanip>

struct Benchmark
{
    std::vector<std::chrono::milliseconds::rep> timings;

    Benchmark(size_t n, std::function<void(void)> const &foo);

    friend std::ostream &operator<<(std::ostream &out, Benchmark const &bm);
};
