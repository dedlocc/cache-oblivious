#pragma once

#ifndef CACHE_OBLIVIOUS_RANDOM_H
#define CACHE_OBLIVIOUS_RANDOM_H

#include <random>

class Random
{
    static inline std::mt19937 engine = std::mt19937{ std::random_device()() };
public:
    template<class T>
    static T next(const T &min, const T &max)
    {
        return std::uniform_int_distribution<T>(min, max)(engine);
    }
};

#endif //CACHE_OBLIVIOUS_RANDOM_H
