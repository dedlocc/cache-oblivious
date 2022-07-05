#pragma once

#include <random>

class Random
{
    static std::mt19937_64 & getEngine()
    {
        static std::mt19937_64 engine = std::mt19937_64 {std::random_device()()};
        return engine;
    }

public:
    template <class T>
    static T next(T min, T max)
    {
        return std::uniform_int_distribution(min, max)(getEngine());
    }
};
