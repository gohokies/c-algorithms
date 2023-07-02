#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "mergesort.h"
#include "insertionsort.h"

#include "sortutils.h"
#include "sortcommon.h"

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

    void* pMid = base + mid * itemsize;
    void* pEnd = base + nitems * itemsize;    

    if (context->compare(pMid - itemsize, pMid) <= 0) return;

    void* p1 = base;
    void* p2 = pMid;
    while (p1 < pMid && p2 < pEnd)
    {
        if (context->compare(p1, p2) < 0)
        {
            context->move(buffer, p1, itemsize);
            p1 += itemsize;
        }
        else
        {
            context->move(buffer, p2, itemsize);
            p2 += itemsize;
        }

        buffer += itemsize;
    }

    while (p1 < pMid)
    { 
        context->move(buffer, p1, itemsize);
        buffer += itemsize;
        p1 += itemsize;
    }

    while (p2 < pEnd)
    {
        memcpy(buffer, p2, itemsize);
        buffer += itemsize;
        p2 += itemsize;
    }

    while (nitems > 0)
    {
        buffer -= itemsize;
        p2 -= itemsize;
        memcpy(p2, buffer, itemsize);
        nitems--;
    }
}

int _merge_sort(
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

    if (nitems < 16)
    {
        return insertion_sort(base, nitems, itemsize, context->compare, basic_move, buffer);
    }

    ret = _merge_sort(context, base, itemsize, nl, buffer);
    if (ret != 0) return ret;
    ret = _merge_sort(context, base + nl * itemsize, itemsize, nitems - nl, buffer + nl * itemsize); 
    if (ret != 0) return ret;

    _merge(context, base, itemsize, nl, nitems, buffer);
    return 0;
}

int merge_sort(
    void *base,
    size_t nitems,
    size_t size,
    CompareFunc compare,
    SwapFunc swap,
    void* buffer
    )
{
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
    context.swap = swap;
    context.move = basic_move;

    res = _merge_sort(&context, base, size, nitems, buffer); 

    if(allocated) free(buffer);
    
    return res;
}
