#ifndef _BLOCK_SORT_HPP_
#define _BLOCK_SORT_HPP_

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <iterator>

#include "insertion_sort.hpp"

namespace algorithms 
{
    size_t _floorOfPowerOfTwo(size_t x)
    {
        for(size_t i = 1; i < sizeof(size_t) * 4; i <<= 1)
        {
            x = x | (x >> i);
        }

        return x - (x >> 1);
    } 

    template<typename RandomIt>
    void _rotate(RandomIt begin, RandomIt mid, RandomIt end)
    {
        while (begin < mid && mid < end)
        {
            RandomIt it = mid;
            size_t l = mid - begin;
            size_t r = end - mid;
            size_t m = l < r? l : r;

            for (size_t i = 0; i < m; i++) std::iter_swap(begin++, it++);
            mid += (l < r) ? l : 0;
        }
    }

    template<typename RandomIt, typename Compare>
    void _merge(RandomIt begin, RandomIt mid, RandomIt end, Compare cmp)
    {
        while (begin < mid && mid < end)
        {
            // Skip items that are already in posions in left part.
            while(cmp(*begin, *mid)) begin++;

            // Find the position for *begine to move to
            RandomIt pos = mid + 1;
            while(pos < end && (!cmp(*begin, *pos))) pos++;

            // Now pos is the position for *begin to move to. Rotate [mid, pos) to and [begin, mid).
            _rotate(begin, mid, pos);

            // calculate the new ranges
            size_t amount = pos - mid;
            begin = begin + amount;
            mid = pos;

            // Skip since *begin is already compared.
            begin++;
        }
    }

    template<typename RandomIt, typename Compare>
    void block_sort(RandomIt begin, RandomIt end, Compare cmp)
    {
        static constexpr size_t MinStep = 16;

        size_t count = end - begin;

        if (count < 2) return;
        if (count < MinStep)
        {
            insertion_sort(begin, end, cmp);
            return;
        }

        size_t powerOfTwo = _floorOfPowerOfTwo(count);
        size_t d = powerOfTwo / MinStep;
        size_t n = (count % powerOfTwo + d - 1) / d;

        // insertion sort all small sections
        RandomIt it = begin;
        size_t remains = 0;
        for (size_t i = 0; i < d; i++)
        {
            size_t k;
            RandomIt it2 = it + MinStep;

            remains += n;
            k = remains / d;
            remains -= k * d;
            it2 += k;
        
            insertion_sort(it, it2, cmp);
            it = it2;
        }

        // If theer is only one section, return;        
        if (d < 2) return;

        // Try to block sort
        size_t step = MinStep;
        size_t nstep = n;
        while (step < count)
        {
            size_t integer_part = 0;
            size_t remains = 0;
            while (integer_part < count)
            {
                size_t k = 0;
                size_t l, m, r;
                
                // Left
                l = integer_part;
                
                // Mid
                integer_part += step;
                remains += nstep;
                k = remains / d;
                remains -= k * d;
                integer_part += k;
                m = integer_part;
                
                // Right
                integer_part += step;
                remains += nstep;
                k = remains / d;
                remains -= k * d;
                integer_part += k;
                r = integer_part;
                
                // Merge left and right
                if (cmp(*(begin + r - 1), *(begin + l)))
                {
                    _rotate(begin + l, begin + m, begin + r);
                }
                else if (cmp(*(begin + m), *(begin + m - 1)))
                {
                //    _merge(begin + l, begin + m, begin + r, cmp);
                    std::inplace_merge(begin + l, begin + m, begin + r, cmp); 
                }
            }

            step += step;
            nstep += nstep;
        }      
    }

    template<typename RandomIt>
    void block_sort(RandomIt begin, RandomIt end)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;
        block_sort(begin, end, std::less<T>());
    }    
}

#endif