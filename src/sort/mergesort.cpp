#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "mergesort.h"
#include "insertionsort.h"

#include "sortutils.h"
#include "sortcommon.h"

#include <algorithm>

static const size_t kInsertSortThreshold = 16;

#define _MERGE_TO(Type, Base, Mid, Items, Buffer)       \
{   Type* pBase = (Type*)base;                          \
    Type* pMid = pBase + Mid;                           \
    Type* pEnd = pBase + Items;                         \
    Type* pBuffer = (Type*)Buffer;                      \
    Type* p1 = pBase;                                   \
    Type* p2 = pMid;                                    \
    while(p1 < pMid && p2 < pEnd){                      \
        if(*p1 < * p2)                                  \
            *pBuffer++=*p1++;                           \
        else                                            \
            *pBuffer++=*p2++;                           \
    }                                                   \
    while(p1 < pMid){ *pBuffer++ = *p1++; }             \
    while(p2 < pEnd){ *pBuffer++ = *p2++; }             \
}

#define _RMERGE_TO(Type, Base, Mid, Items, Buffer)      \
{   Type* pBase = (Type*)base;                          \
    Type* pMid = pBase + Mid;                           \
    Type* pEnd = pBase + Items;                         \
    Type* pBuffer = (Type*)Buffer;                      \
    Type* p1 = pBase;                                   \
    Type* p2 = pMid;                                    \
    while(p1 < pMid && p2 < pEnd){                      \
        if(*p1 > * p2)                                  \
            *pBuffer++=*p1++;                           \
        else                                            \
            *pBuffer++=*p2++;                           \
    }                                                   \
    while(p1 < pMid){ *pBuffer++ = *p1++; }             \
    while(p2 < pEnd){ *pBuffer++ = *p2++; }             \
}

#define _MERGE_CMP(Type, Base, Mid, Items, Cmp, Buffer) \
{   Type* pBase = (Type*)base;                          \
    Type* pMid = pBase + Mid;                           \
    Type* pEnd = pBase + Items;                         \
    Type* pBuffer = (Type*)Buffer;                      \
    Type* p1 = pBase;                                   \
    Type* p2 = pMid;                                    \
    while(p1 < pMid && p2 < pEnd){                      \
        if(Cmp(p1,p2))                                  \
            *pBuffer++=*p1++;                           \
        else                                            \
            *pBuffer++=*p2++;                           \
    }                                                   \
    while(p1 < pMid){ *pBuffer++ = *p1++; }             \
    while(p2 < pEnd){ *pBuffer++ = *p2++; }             \
}

int _merge_sort_uint32(uint32_t *base, size_t nitems, uint32_t* buffer)
{
    int res = 0;

    if (nitems < 2) return res;
    if (nitems <= kInsertSortThreshold) return insertion_sort_uint32(base, nitems);
    
    size_t nl = nitems >> 1;
    if ((res = _merge_sort_uint32(base, nl, buffer)) != 0) return res;
    if ((res = _merge_sort_uint32(base + nl, nitems - nl, buffer + nl)) != 0) return res; 

    _MERGE_TO(uint32_t, base, nl, nitems, buffer);
    memcpy(base, buffer, nitems * sizeof(uint32_t));

    return 0;
}

static inline void _merge_s4(
    void *base,
    size_t mid,
    size_t nitems,
    CompareFunc cmp, 
    void* buffer
    )
{
    _MERGE_CMP(uint32_t, base, mid, nitems, cmp, buffer);
}

static inline void _merge_s8(
    void *base,
    size_t mid,
    size_t nitems,
    CompareFunc cmp, 
    void* buffer
    )
{
    _MERGE_CMP(uint64_t, base, mid, nitems, cmp, buffer);
}

static void _merge_generic(
    void *base,
    size_t itemsize,
    size_t mid,
    size_t nitems,
    CompareFunc cmp,
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
        if (cmp(p1, p2))
        {
            memcpy(pBuffer, p1, itemsize); p1 += itemsize;
        }
        else
        {
            memcpy(pBuffer, p2, itemsize); p2 += itemsize;
        }

        pBuffer += itemsize;
    }

    while(p1 < pMid){ memcpy(pBuffer, p1, itemsize); pBuffer += itemsize; p1 += itemsize; }
    while(p2 < pEnd){ memcpy(pBuffer, p2, itemsize); pBuffer += itemsize; p2 += itemsize; }
}

static inline void _merge(
    void *base,
    size_t itemsize,
    size_t mid,
    size_t nitems,
    CompareFunc cmp,
    void* buffer
    )
{
    switch(itemsize)
    {
        case 4:
            _MERGE_CMP(uint32_t, base, mid, nitems, cmp, buffer);
            break;
        case 8:
            _MERGE_CMP(uint64_t, base, mid, nitems, cmp, buffer);
            break;
        default:
            _merge_generic(base, itemsize, mid, nitems, cmp, buffer);
            break;
    }
}

static int _merge_sort(
    void *base,
    size_t itemsize,
    size_t nitems,
    CompareFunc cmp,
    void* buffer
    )
{
    int ret = 0;

    if (nitems < 2) return 0;

    if (nitems <= kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, itemsize, cmp);
    }

    uint8_t* pBase = (uint8_t*)base;
    uint8_t* pBuffer = (uint8_t*)buffer;
    size_t nl = nitems >> 1;
    ret = _merge_sort(pBase, itemsize, nl, cmp, buffer);
    if (ret != 0) return ret;
    ret = _merge_sort(pBase + nl * itemsize, itemsize, nitems - nl, cmp, pBuffer + nl * itemsize); 
    if (ret != 0) return ret;

    _merge(pBase, itemsize, nl, nitems, cmp, pBuffer);
    memcpy(pBase, pBuffer, nitems * itemsize);

    return 0;
}

static int _quad_sort(
    void *base,
    size_t itemsize,
    size_t nitems,
    CompareFunc cmp,
    void* buffer
    )
{
    int r = 0;

    if (nitems < 2) return 0;

    // Switch to insertion sort threshold.
    if (nitems <= kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, itemsize, cmp);
    }

    // Divide source items to 4 parts, and sort each of them.
    size_t mid = (nitems >> 1);
    size_t offset = 0;
    uint8_t* pBase = (uint8_t*)base;
    uint8_t* pBuffer = (uint8_t*)buffer;    

    // Left part
    size_t lmid = (mid >> 1);
    if((r = _quad_sort(pBase, itemsize, lmid, cmp, pBuffer)) != 0) return r;
    offset = itemsize * lmid;
    if((r = _quad_sort(pBase + offset, itemsize, mid - lmid, cmp, pBuffer + offset)) != 0) return r;
    
    // Right part
    size_t rmid = ((nitems - mid) >> 1);
    offset = itemsize * mid;
    if((r = _quad_sort(pBase + offset, itemsize, rmid, cmp, pBuffer + offset)) != 0) return r;
    offset += rmid * itemsize;
    if((r = _quad_sort(pBase + offset, itemsize, nitems - mid - rmid, cmp, pBuffer + offset)) != 0) return r;

    // Merge 4 sorted parts to auxiliray array, and merge back in place. 
    _merge(pBase, itemsize, lmid, mid, cmp, pBuffer);
    _merge(pBase + mid * itemsize, itemsize, rmid, nitems - mid, cmp, pBuffer + mid * itemsize);
    _merge(pBuffer, itemsize, mid, nitems, cmp, pBase);

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
        return insertion_sort(base, nitems, size, compare);
    }

    uint8_t* pBuffer = (uint8_t*)buffer;
    if(pBuffer == NULL)
    {
        pBuffer = (uint8_t*)malloc(nitems * size);
        if(pBuffer == NULL) return -1;
    }

    res = _merge_sort(base, size, nitems, compare, pBuffer); 

    if(pBuffer != buffer) free(pBuffer);
    
    return res;
}

int merge_sort_uint32(
    uint32_t* base,
    size_t nitems,
    void* buffer
    )
{
    int res = 0;

    // Switch to insertion sort threshold.
    if (nitems < kInsertSortThreshold)
    {
        return insertion_sort_uint32(base, nitems);
    }

    uint8_t* pBuffer = (uint8_t*)buffer;
    if(pBuffer == NULL)
    {
        pBuffer = (uint8_t*)malloc(nitems * sizeof(uint32_t));
        if(pBuffer == NULL) return -1;
    }

    res = _merge_sort_uint32(base, nitems, (uint32_t*)pBuffer); 

    if(pBuffer != buffer) free(pBuffer);
    
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
    int res = 0;

    // Switch to insertion sort threshold.
    if (nitems < kInsertSortThreshold)
    {
        return insertion_sort(base, nitems, size, compare);
    }

    uint8_t* pBuffer = (uint8_t*)buffer;
    if (pBuffer == NULL)
    {
        pBuffer = (uint8_t*)malloc(nitems * size);
        if (pBuffer == NULL) return -1;
    }

    res = _quad_sort(base, size, nitems, compare, pBuffer); 

    if(pBuffer != buffer) free(pBuffer);
    
    return res;
}
