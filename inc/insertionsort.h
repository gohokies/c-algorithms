#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_

#pragma once

#include "sortbase.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Sorts [begin, end) using insertion sort with the given comparison function.
int insertion_sort(void* base, size_t nItems, size_t sizeElem, CompareFunc cmp, MoveFunc mv);

#ifdef __cplusplus
}
#endif

#endif