#include "Benchmark.h"

using namespace std::chrono;

Benchmark::Benchmark(const size_t &n, const std::function<void(void)> &foo)
{
	timings.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        const auto start = high_resolution_clock::now();
        foo();
        const auto stop = high_resolution_clock::now();
        timings.emplace_back(duration_cast<milliseconds>(stop - start).count());
    }
}

std::ostream &operator<<(std::ostream &out, const Benchmark &m)
{
	auto sum = duration_values<milliseconds::rep>::zero();
	for (const auto &t : m.timings) {
		sum += t;
	}

    //out << "avg: " << std::left << std::setw(8) << (sum + m.timings.size() / 2) / m.timings.size()
    //    << "sum: " << sum << '\n';

	for (const auto &t : m.timings) {
		out << t << ' ';
	}

    return out;
}