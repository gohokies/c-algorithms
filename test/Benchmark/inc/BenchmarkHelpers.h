#pragma once

#include <ctime>
#include <algorithm>
#include <random>
#include <string>

#include "sortbase.h"

namespace Benchmark
{
    template<typename T>
    struct Comparer
    {
    private:
        CompareFunc _cmp;
    public:
        Comparer(CompareFunc cmp) : _cmp(cmp) {}

        constexpr bool operator()(const T& lhs, const T& rhs) const
        {
            return _cmp(&lhs, &rhs);
        }
    };

    template<typename T>
    inline bool Compare(const void* lhs, const void* rhs)
    {
        return *static_cast<const T*>(lhs) < *static_cast<const T*>(rhs);
    }

    template<typename T>
    inline bool ReverseCompare(const void* lhs, const void* rhs)
    {
        return *static_cast<const T*>(rhs) < *static_cast<const T*>(lhs);
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