#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <iterator>

namespace algorithms 
{
    template<typename RandomIt, typename Compare>
    void heap_sort(RandomIt begin, RandomIt end, Compare cmp)
    {
        std::make_heap(begin, end, cmp);
        std::sort_heap(begin, end, cmp);
    }

    template<typename RandomIt>
    void heap_sort(RandomIt begin, RandomIt end)
    {
        std::make_heap(begin, end);
        std::sort_heap(begin, end);
    }
}

#endif