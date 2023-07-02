#pragma once

#include <ctime>
#include <algorithm>
#include <random>
#include <string>

namespace Benchmark
{
    template<typename T>
    inline int Compare(const void* lhs, const void* rhs)
    {
        const T* l = static_cast<const T*>(lhs); 
        const T* r = static_cast<const T*>(rhs);
        if (*l == *r) return 0; 
        return (*l < *r) ? -1 : 1;
    }

    template<typename T>
    inline void Swap(void* lhs, void* rhs)
    {
        T* l = static_cast<T*>(lhs); 
        T* r = static_cast<T*>(rhs);
        T v = std::move(*l);
        *l = std::move(*r);
        *r = std::move(v);
    }

    template<typename T>
    inline void Move(void* dst, void* src)
    {
        T* d = static_cast<T*>(dst); 
        T* s = static_cast<T*>(src);
        *d = std::move(*s);
    }

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