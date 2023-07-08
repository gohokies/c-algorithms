#ifndef _INSERTION_SORT_HPP_
#define _INSERTION_SORT_HPP_

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <iterator>

namespace algorithms 
{
    constexpr size_t kInsertSortThreshold = 16;

    // Sorts [begin, end) using insertion sort with the given comparison function.
    template<typename RandomIt, typename Compare>
    void insertion_sort(RandomIt begin, RandomIt end, Compare cmp)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        if (begin == end) return;

        for (RandomIt it = begin + 1; it != end; ++it) 
        {
            RandomIt cur = it;
            RandomIt cur_1 = it - 1;

            // Compare first to avoid 2 moves for an element already positioned correctly.
            if (cmp(*cur, *cur_1))
            {
                T tmp = std::move(*cur);

                do
                { 
                    *cur-- = std::move(*cur_1);
                }
                while(cur != begin && cmp(tmp, *--cur_1));

                *cur = std::move(tmp);
            }
        }
    }

    // Sorts [begin, end) using insertion sort with the given comparison function. Assumes
    // *(begin - 1) is an element smaller than or equal to any element in [begin, end).
    template<class RandomIt, class Compare>
    inline void insertion_sort_unguarded(RandomIt begin, RandomIt end, Compare cmp)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        if (begin == end) return;

        for (RandomIt it = begin + 1; it != end; ++it)
        {
            RandomIt cur = it;
            RandomIt cur_1 = it - 1;

            // Compare first to avoid 2 moves for an element already positioned correctly.
            if (cmp(*cur, *cur_1))
            {
                T tmp = std::move(*cur);

                do
                { 
                    *cur-- = std::move(*cur_1);
                }
                while(cmp(tmp, *--cur_1));

                *cur = std::move(tmp);
            }
        }
    }
}

#endif