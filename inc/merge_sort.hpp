#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <iterator>

#include "insertion_sort.hpp"

namespace algorithms 
{
    /*
    template<typename RandomIt, typename Compare>
    void _merge_(RandomIt begin, RandomIt mid, RandomIt end, Compare cmp, RandomIt dstBegin)
    {
        RandomIt s1 = begin;
        RandomIt s2 = mid;
        
        while(s1 < mid && s2 < end)
        {
            if (cmp(*s1, *s2))
            {
                *dstBegin = std::move(*s1);
                s1++;
            }
            else
            {
                *dstBegin = std::move(*s2);
                s2++;
            }

            dstBegin++;
        }

        while(s1 < mid) { *dstBegin++ = std::move(*s1); s1++; }
        while(s2 < end) { *dstBegin++ = std::move(*s2); s2++; }
    }
    */

    template<typename RandomIt, typename Compare>
    void _merge_sort(RandomIt begin, RandomIt end, Compare cmp, RandomIt auxBegin)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        size_t count = end - begin;
        if (count < 2) return;

        // Switch to insertion sort threshold.
        if (count < kInsertSortThreshold)
        {
            insertion_sort(begin, end, cmp);
            return;
        }

        // Divide source items to 4 parts, and sort each of them.
        RandomIt mid = begin + (count >> 1);
        RandomIt auxMid = auxBegin + (count >> 1);
        size_t lcount = mid - begin;
        size_t rcount = end - mid;
        RandomIt lmid = begin + (lcount >> 1);
        RandomIt rmid = mid + (rcount >> 1);
        RandomIt aux = auxBegin;
        _merge_sort(begin, lmid, cmp, aux);
        aux += lcount >> 1;
        _merge_sort(lmid, mid, cmp, aux);
        aux = auxMid;
        _merge_sort(mid, rmid, cmp, aux);
        aux += rcount >> 1;
        _merge_sort(rmid, end, cmp, aux);

        // Merge 4 sorted parts to auxiliray array, and merge back in place. 
        //_merge_(begin, lmid, mid, cmp, auxBegin);
        //_merge_(mid, rmid, end, cmp, auxMid);
        //_merge_(auxBegin, auxMid, auxBegin + count, cmp, begin);        
        std::merge(begin, lmid, lmid, mid, auxBegin, cmp);
        std::merge(mid, rmid, rmid, end, auxMid, cmp);
        std::merge(auxBegin, auxMid, auxMid, auxBegin + count, begin, cmp);
    }

    // Use auxiliry buffer to sort [begin, end). Caller needs to make sure that the 
    // auxiliry buffer must no less than the number of the items to sort. The
    // sorted array is in place in [begin, end).
    template<typename RandomIt, typename Compare>
    void merge_sort(RandomIt begin, RandomIt end, Compare cmp, RandomIt dstBegin)
    {
        _merge_sort(begin, end, cmp, dstBegin);
    }

    // Allocate auxiliary buffer, the use it to do merge sort.
    template<typename RandomIt, typename Compare>
    void merge_sort(RandomIt begin, RandomIt end, Compare cmp)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;
        std::vector<T> buffer;
        size_t count = (end - begin);
    
        buffer.resize(count);
        _merge_sort(begin, end, cmp, buffer.begin());
    }

    template<typename RandomIt>
    void merge_sort(RandomIt begin, RandomIt end)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;
        merge_sort(begin, end, std::less<T>());
    }

    template<typename RandomIt, typename Compare>
    void merge_sort_inplace(RandomIt begin, RandomIt end, Compare cmp)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        size_t count = end - begin;
        if (count < 2) return;

        // Switch to insertion sort threshold.
        if (count < kInsertSortThreshold)
        {
            insertion_sort(begin, end, cmp);
            return;
        }

        // Divide source items to 2 parts, and sort each of them.
        RandomIt mid = begin + (count >> 1);
        merge_sort_inplace(begin, mid, cmp);
        merge_sort_inplace(mid, end, cmp);
        std::inplace_merge(begin, mid, end, cmp);
    }

    template<typename RandomIt>
    void merge_sort_inplace(RandomIt begin, RandomIt end)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;
        merge_sort_inplace(begin, end, std::less<T>());
    }    
}

#endif