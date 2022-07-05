#pragma once

#include "Random.h"

template <class T>
class Matrix
{
public:
    explicit Matrix(size_t size, T min, T max);

    Matrix(const Matrix &) = delete;

    void transposeNaive();

    void transposeCacheOblivious(size_t blockSize = 32);

    template <class U>
    friend std::ostream & operator<<(std::ostream &, const Matrix<U> &);

private:
    size_t const size;
    std::vector<T> arr;

    void swapAt(size_t x, size_t y);

    void transposeCacheOblivious(size_t x0, size_t y0, size_t dx, size_t dy, size_t blockSize);
};

#include "Matrix.tpp"
