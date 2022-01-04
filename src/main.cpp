#include <iostream>
#include <fstream>

#include "Matrix.h"
#include "Benchmark.h"

int main()
{
    std::ofstream fout("out.txt");

    size_t constexpr BENCHMARKS = 20;

    for (size_t i = 2500; i <= 50000; i += 2500) {
        std::cout << "Running for " << i << 'x' << i << " matrices" << std::endl;

        Matrix<char8_t> m(i, 0, 9);

        fout << i << '\n'
            // Naive
            << Benchmark(BENCHMARKS, [&m] { m.transposeNaive(); }) << '\n'
            // No blocks
            << Benchmark(BENCHMARKS, [&m] { m.transposeCacheOblivious(1); }) << '\n'
            // 64x64 blocks
            << Benchmark(BENCHMARKS, [&m] { m.transposeCacheOblivious(64); }) << '\n'
            // 512x512 blocks
            << Benchmark(BENCHMARKS, [&m] { m.transposeCacheOblivious(512); }) << '\n'
            << std::endl;
    }

    return 0;
}