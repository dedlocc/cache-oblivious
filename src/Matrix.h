#pragma once

#ifndef CACHE_OBLIVIOUS_MATRIX_H
#define CACHE_OBLIVIOUS_MATRIX_H

#include "Random.h"

template<class T>
class Matrix
{
public:
    explicit Matrix(const size_t &, const T &, const T &);

    ~Matrix();

    void transposeNaive();

    void transposeCacheOblivious(const size_t & = 32);

    template<class T_>
    friend std::ostream &operator<<(std::ostream &, const Matrix<T_> &);

private:
    const size_t size;
    T **arr;

    T **alloc(const size_t &);

    void free(T **&);

    void transposeCacheOblivious(const size_t &, const size_t &, const size_t &, const size_t &, const size_t &, T **&);
};

#include "Matrix.tpp"

#endif //CACHE_OBLIVIOUS_MATRIX_H
