#ifndef _MERGESORT_H_
#define _MERGESORT_H_

#include <stdlib.h>
#include "sortbase.h"

#ifdef __cplusplus
extern "C"
{
#endif

int merge_sort(
    void *base,
    size_t items,
    size_t size,
    CompareFunc compare,
    SwapFunc swap,
    void* buffer
    );

int quad_sort(
    void *base,
    size_t items,
    size_t size,
    CompareFunc compare,
    SwapFunc swap,
    void* buffer
    );

#ifdef __cplusplus
}
#endif

#endif