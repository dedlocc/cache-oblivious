#include <iostream>
#include <fstream>

#include "Matrix.h"
#include "Benchmark.h"

int main()
{
    std::ofstream fout("out.txt");

    for (size_t i = 2500; i <= 50000; i += 2500) {
        std::cout << i << std::endl;
        Matrix<char8_t> m(i, 0, 10);
        fout << i << '\n'
            // Naive
            << Benchmark(20, [&m] { m.transposeNaive(); }) << '\n'
            // No blocks
            << Benchmark(20, [&m] { m.transposeCacheOblivious(1); }) << '\n'
            // 64x64 blocks
            << Benchmark(20, [&m] { m.transposeCacheOblivious(64); }) << '\n'
            // 512x512 blocks
            << Benchmark(20, [&m] { m.transposeCacheOblivious(512); }) << '\n' << std::endl;
    }

    return 0;
}