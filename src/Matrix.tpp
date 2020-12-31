#include "Matrix.h"

#include <cstddef>
#include <algorithm>
#include <iomanip>

template<class T>
Matrix<T>::Matrix(const size_t &size, const T &min, const T &max)
    : size(size), arr(alloc(size))
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            arr[i][j] = Random::next(min, max);
        }
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    free(arr);
}

template<class T>
void Matrix<T>::transposeNaive()
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            std::swap(arr[i][j], arr[j][i]);
        }
    }
}

template<class T>
void Matrix<T>::transposeCacheOblivious(const size_t &block)
{
    auto a = alloc(size);
    transposeCacheOblivious(0, 0, size, size, block, a);
    free(arr);
    arr = std::move(a);
}

template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &m)
{
    for (size_t i = 0; i < m.size; ++i) {
        for (size_t j = 0; j < m.size; ++j) {
            out << std::setw(2) << std::left << (uint32_t) m.arr[i][j] << ' ';
        }
        out << '\n';
    }

    return out;
}

template<class T>
T **Matrix<T>::alloc(const size_t &size)
{
    T **a = new T *[size];
    for (size_t i = 0; i < size; ++i) {
        a[i] = new T[size];
    }

    return a;
}

template<class T>
void Matrix<T>::free(T **&a)
{
    for (size_t i = 0; i < size; ++i) {
        delete a[i];
    }

    delete[] a;
}

template<class T>
void Matrix<T>::transposeCacheOblivious(
    const size_t &x0,
    const size_t &y0,
    const size_t &dx,
    const size_t &dy,
    const size_t &block,
    T **&a
) {
    if (1 == dx && 1 == dy) {
        a[y0][x0] = arr[x0][y0];
        return;
    }

    if (dx <= block && dy <= block) {
        const auto x1 = x0 + dx;
        const auto y1 = y0 + dy;
        for (size_t i = x0; i < x1; ++i) {
            for (size_t j = y0; j < y1; ++j) {
                a[i][j] = arr[j][i];
            }
        }
        return;
    }

    if (dy <= dx) {
        const auto mid = dx / 2;
        transposeCacheOblivious(x0, y0, mid, dy, block, a);
        transposeCacheOblivious(x0 + mid, y0, dx - mid, dy, block, a);
        return;
    }

    const auto mid = dy / 2;
    transposeCacheOblivious(x0, y0, dx, mid, block, a);
    transposeCacheOblivious(x0, y0 + mid, dx, dy - mid, block, a);
}