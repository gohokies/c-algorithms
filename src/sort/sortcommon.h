#ifndef _SORTCOMMON_H_
#define _SORTCOMMON_H_

#include "sortbase.h"
#include "sortutils.h"

struct SortContext
{
    CompareFunc compare;
    swap_type swaptype;
    uint8_t* buffer;
};

int _sort2(void* x1, void* x2, CompareFunc cmp, SwapFunc swap);

int _sort3(void* x1, void* x2, void* x3, CompareFunc cmp, SwapFunc swap);

int _sort4(void* x1, void* x2, void* x3, void* x4, CompareFunc cmp, SwapFunc swap);

int _sort5(void* x1, void* x2, void* x3, void* x4, void* x5, CompareFunc cmp, SwapFunc swap);

int _small_sort(void* base, size_t nitems, size_t sizeElem, CompareFunc cmp, SwapFunc swap);

size_t _checksum(void* base, size_t nitems, size_t sizeElem);

#endif