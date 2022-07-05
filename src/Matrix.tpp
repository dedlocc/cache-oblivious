#include "Matrix.h"

#include <cstddef>
#include <algorithm>
#include <iomanip>

template <class T>
Matrix<T>::Matrix(size_t size, T min, T max)
    : size(size)
    , arr(size * size)
{
    std::generate(arr.begin(), arr.end(), [=]() {
        return Random::next(min, max);
    });
}

template <class T>
void Matrix<T>::transposeNaive()
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            swapAt(i, j);
        }
    }
}

template <class T>
void Matrix<T>::transposeCacheOblivious(size_t blockSize)
{
    transposeCacheOblivious(0, 0, size, size, blockSize);
}

template <class T>
std::ostream & operator<<(std::ostream & out, const Matrix<T> & m)
{
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            out << (int) m.arr[i * m.size + j] << ' ';
        }
        out << '\n';
    }

    return out;
}

template <class T>
void Matrix<T>::swapAt(size_t x, size_t y)
{
    using std::swap;
    return swap(arr[x * size + y], arr[y * size + x]);
}

template <class T>
void Matrix<T>::transposeCacheOblivious(size_t x0, size_t y0, size_t dx, size_t dy, size_t blockSize)
{
    if (dx <= blockSize && dy <= blockSize) {
        auto x1 = x0 + dx;
        auto y1 = y0 + dy;
        for (size_t i = x0; i < x1; ++i) {
            for (size_t j = std::max(i + 1, y0); j < y1; ++j) {
                swapAt(i, j);
            }
        }
        return;
    }

    if (dy <= dx) {
        auto mid = dx / 2;
        transposeCacheOblivious(x0, y0, mid, dy, blockSize);
        transposeCacheOblivious(x0 + mid, y0, dx - mid, dy, blockSize);
        return;
    }

    auto mid = dy / 2;
    transposeCacheOblivious(x0, y0, dx, mid, blockSize);
    transposeCacheOblivious(x0, y0 + mid, dx, dy - mid, blockSize);
}
