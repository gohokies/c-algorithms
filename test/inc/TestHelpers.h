#pragma once

#include <ctime>
#include <algorithm>
#include <random>
#include <string>

namespace Test
{
    template<typename T>
    void fill_random_values(T* arr, size_t size, T delta)
    {
        int32_t r = 0;

        if (sizeof(T) < sizeof(int32_t)) r = sizeof(int32_t) - sizeof(T);

        std::srand(static_cast<unsigned int>(std::time(NULL)));
        for(size_t i = 0; i < size; i++)
        {
            arr[i] = static_cast<T>(std::rand() >> r) - delta;
        }
    }
}