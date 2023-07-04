#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "mergesort.h"
#include "insertionsort.h"

#include "sortutils.h"
#include "sortcommon.h"

static const size_t kInsertSortThreshold = 16;

static void _merge(
    struct SortContext* context,
    void *base,
    size_t itemsize,
    size_t mid,
    size_t nitems,
    void* buffer
    )
{
    assert(mid > 0);
    assert(nitems  > 0);

    uint8_t* pBase = (uint8_t*)base;
    uint8_t* pMid = pBase + mid * itemsize;
    uint8_t* pEnd = pBase + nitems * itemsize;    
    uint8_t* pBuffer = (uint8_t*)buffer;

    uint8_t* p1 = pBase;
    uint8_t* p2 = pMid;
    while (p1 < pMid && p2 < pEnd)
    {
        if (context->compare(p1, p2) < 0)
        {
            memcpy(pBuffer, p1, itemsize);
            p1 += itemsize;
        }
        else
        {
            memcpy(pBuffer, p2, itemsize);
            p2 += itemsize;
        }

        pBuffer += itemsize;
    }

    while (p1 < pMid)
    { 
        memcpy(pBuffer, p1, itemsize);
        pBuffer += itemsize;
        p1 += itemsize;
    }

    while (p2 < pEnd)
    {
        memcpy(pBuffer, p2, itemsize);
        pBuffer += itemsize;
        p2 += itemsize;
    }
}

static int _merge_sort(
    struct SortContext* context,
    void *base,
    size_t itemsize,
    size_t nitems,
    void* buffer
    )
{
    int ret = 0;
    size_t nl = nitems >> 1;

    if (nitems < 2) return 0;

    if (nitems <= kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, itemsize, context->compare, basic_move);
    }

    ret = _merge_sort(context, base, itemsize, nl, buffer);
    if (ret != 0) return ret;
    ret = _merge_sort(context, base + nl * itemsize, itemsize, nitems - nl, buffer + nl * itemsize); 
    if (ret != 0) return ret;

    _merge(context, base, itemsize, nl, nitems, buffer);
    memcpy(base, buffer, nitems * itemsize);

    return 0;
}

static int _quad_sort(
    struct SortContext* context,
    void *base,
    size_t itemsize,
    size_t nitems,
    void* buffer
    )
{
    int r = 0;

    if (nitems < 2) return 0;

    // Switch to insertion sort threshold.
    if (nitems <= kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, itemsize, context->compare, basic_move);
    }

    // Divide source items to 4 parts, and sort each of them.
    size_t mid = (nitems >> 1);
    size_t offset = 0;
    uint8_t* pBase = (uint8_t*)base;
    uint8_t* pBuffer = (uint8_t*)buffer;    

    // Left part
    size_t lmid = (mid >> 1);
    if((r = _quad_sort(context, pBase, itemsize, lmid, pBuffer)) != 0) return r;
    offset = itemsize * lmid;
    if((r = _quad_sort(context, pBase + offset, itemsize, mid - lmid, pBuffer + offset)) != 0) return r;
    
    // Right part
    size_t rmid = ((nitems - mid) >> 1);
    offset = itemsize * mid;
    if((r = _quad_sort(context, pBase + offset, itemsize, rmid, pBuffer + offset)) != 0) return r;
    offset += rmid * itemsize;
    if((r = _quad_sort(context, pBase + offset, itemsize, nitems - mid - rmid, pBuffer + offset)) != 0) return r;

    // Merge 4 sorted parts to auxiliray array, and merge back in place. 
    _merge(context, pBase, itemsize, lmid, mid, pBuffer);
    _merge(context, pBase + mid * itemsize, itemsize, rmid, nitems - mid, pBuffer + mid * itemsize);
    _merge(context, pBuffer, itemsize, mid, nitems, pBase);

    return r;
}

int merge_sort(
    void *base,
    size_t nitems,
    size_t size,
    CompareFunc compare,
    void* buffer
    )
{
    int res = 0;

    // Switch to insertion sort threshold.
    if (nitems < kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, size, compare, basic_move);
    }

    int allocated = 0;
    if (buffer == NULL)
    {
        buffer = malloc(nitems * size);
        if (buffer == NULL) return -1;
        allocated = 1;
    }

    struct SortContext context;
    context.compare = compare;
    context.buffer = NULL;

    res = _merge_sort(&context, base, size, nitems, buffer); 

    if(allocated) free(buffer);
    
    return res;
}

int quad_sort(
    void *base,
    size_t nitems,
    size_t size,
    CompareFunc compare,
    void* buffer
    )
{
    // Switch to insertion sort threshold.
    if (nitems < kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, size, compare, basic_move);
    }

    int res = 0;
    int allocated = 0;
    struct SortContext context;

    if (buffer == NULL)
    {
        buffer = malloc(nitems * size);
        if (buffer == NULL) return -1;
        allocated = 1;
    }

    context.compare = compare;
    context.buffer = NULL;

    res = _quad_sort(&context, base, size, nitems, buffer); 

    if(allocated) free(buffer);
    
    return res;
}
