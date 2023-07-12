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
    template<typename RandomIt, typename Compare>
    void merge_sort_inplace(RandomIt begin, RandomIt end, Compare cmp)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        size_t count = end - begin;
        if (count < 2) return;

        // Switch to insertion sort threshold.
        if (count <= kInsertSortThreshold)
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

    template<typename RandomIt, typename Compare>
    class MergeSorter
    {
    public:
        MergeSorter(RandomIt begin, RandomIt end, Compare cmp) : _cmp(cmp)
        {
            _buf.resize(kBufferSize);
            _Sort(begin, end, _buf.begin());
        }
    private:
        typedef typename std::iterator_traits<RandomIt>::value_type T;

        static const size_t kBufferSize = 256; 
        std::vector<T> _buf;
        Compare _cmp;

        template<typename RandomIt2>
        void _Merge(RandomIt begin, RandomIt mid, RandomIt end, RandomIt2 dstBegin)
        {
            if (begin == mid || mid == end) return;
            if (_cmp(*(mid-1), *mid)) return;

            // Move left part to buffer
            RandomIt2 dstEnd = std::move(begin, mid, dstBegin);

            // Merge
            while(dstBegin < dstEnd && mid < end)
            {
                if (_cmp(*dstBegin, *mid))
                {
                    *begin = std::move(*dstBegin++);
                }
                else
                {
                    *begin= std::move(*mid++);
                }

                ++begin;
            }

            std::move(dstBegin, dstEnd, std::move(mid, end, begin));
        }

        template<typename BufIt>
        void _Sort(RandomIt begin, RandomIt end, BufIt auxBegin)
        {
            size_t count = std::distance(begin, end);
            
            if (count < 2) return;

            // Switch to insertion sort threshold.
            if (count <= kInsertSortThreshold)
            {
                insertion_sort(begin, end, _cmp);
                return;
            }

            size_t nl = count >> 1;
            size_t nr = count - nl;
            RandomIt mid = begin + nl;
            if (count <= kBufferSize)
            {
                // Divide source items to 4 parts, and sort each of them.
                BufIt auxMid = auxBegin + nl;
                RandomIt lmid = begin + (nl >> 1);
                RandomIt rmid = mid + (nr >> 1);
                BufIt aux = auxBegin;
                _Sort(begin, lmid, aux);
                aux += nl >> 1;
                _Sort(lmid, mid, aux);
                aux = auxMid;
                _Sort(mid, rmid, aux);
                aux += nr >> 1;
                _Sort(rmid, end, aux);

                // Merge 4 sorted parts to auxiliray array, and merge back in place. 
                //_merge_(begin, lmid, mid, cmp, auxBegin);
                //_merge_(mid, rmid, end, cmp, auxMid);
                //_merge_(auxBegin, auxMid, auxBegin + count, cmp, begin);        
                std::merge(begin, lmid, lmid, mid, auxBegin, _cmp);
                std::merge(mid, rmid, rmid, end, auxMid, _cmp);
                std::merge(auxBegin, auxMid, auxMid, auxBegin + count, begin, _cmp);
            }
            else if (count + count <= kBufferSize)
            {
                _Sort(begin, mid, auxBegin);
                _Sort(mid, end, auxBegin);
                _Merge(begin, mid, end, auxBegin);
            }
            else
            {
                _Sort(begin, mid, auxBegin);
                _Sort(mid, end, auxBegin);
                std::inplace_merge(begin, mid, end, _cmp);
            }
        }
    };

    template<typename RandomIt, typename Compare>
    void merge_sort(RandomIt begin, RandomIt end, Compare cmp)
    {
        MergeSorter<RandomIt,Compare> sorter(begin, end, cmp);
    }

    template<typename RandomIt>
    void merge_sort(RandomIt begin, RandomIt end)
    {
        typedef typename std::iterator_traits<RandomIt>::value_type T;
        merge_sort(begin, end, std::less<T>());
    }
}

#endif