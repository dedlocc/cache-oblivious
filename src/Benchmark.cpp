#include <numeric>
#include "Benchmark.h"

using namespace std::chrono;

Benchmark::Benchmark(size_t n, std::function<void(void)> const &foo)
{
    timings.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        auto start = high_resolution_clock::now();
        foo();
        auto stop = high_resolution_clock::now();
        timings.emplace_back(duration_cast<milliseconds>(stop - start).count());
    }
}

std::ostream &operator<<(std::ostream &out, Benchmark const &bm)
{
    auto sum = std::reduce(bm.timings.begin(), bm.timings.end());

    out << "avg: " << std::left << std::setw(8) << (sum + bm.timings.size() / 2) / bm.timings.size()
        << "sum: " << sum << '\n';

    for (auto &t : bm.timings) {
        out << t << ' ';
    }

    return out;
}