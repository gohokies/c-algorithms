#include "sortcommon.h"
#include "insertionsort.h"
/*
// stable, 1 compare, 0-1 swaps
int _sort2(void* x1, void* x2, CompareFunc cmp, SwapFunc swap)
{
    int r = 0;

    if (cmp(x2, x1) < 0) { swap(x1, x2); r++; }

    return r;
}

// stable, 2-3 compares, 0-2 swaps
int _sort3(void* x, void* y, void* z, CompareFunc cmp, SwapFunc swap)
{
    int __r = 0;
    if (cmp(x, y) <= 0)            // if x <= y
    {
        if (cmp(y, z) <= 0)        // if y <= z
            return __r;            // x <= y && y <= z
                                   // x <= y && y > z
        swap(y, z);                // x <= z && y < z
        __r = 1;
        if (cmp(x, y) > 0)         // if x > y
        {
            swap(x, y);            // x < y && y <= z
            __r = 2;
        }
        return __r;                // x <= y && y < z
    }
    if (cmp(y, z) > 0)             // x > y, if y > z
    {
        swap(x, z);                // x < y && y < z
        __r = 1;
        return __r;
    }
    swap(x, y);                    // x > y && y <= z
    __r = 1;                       // x < y && x <= z
    if (cmp(y, z) > 0)             // if y > z
    {
        swap(y, z);                // x <= y && y < z
        __r = 2;
    }
    return __r;
}

int _sort3arr(void* x, size_t sizeElem, CompareFunc cmp, SwapFunc swap);

// stable, 3-6 compares, 0-5 swaps
int _sort4(void* x1, void* x2, void* x3, void* x4, CompareFunc cmp, SwapFunc swap)
{
    int __r = __sort3(x1, x2, x3, cmp, swap);
    if (cmp(x4, x3) < 0)
    {
        swap(x3, x4);
        ++__r;
        if (cmp(x3, x2) < 0)
        {
            swap(x2, x3);
            ++__r;
            if (cmp(x2, x1) < 0)
            {
                swap(x1, x2);
                ++__r;
            }
        }
    }

    return __r;
}


// stable, 4-10 compares, 0-9 swaps
int _sort5(void* x1, void* x2, void* x3, void* x4, void* x5, CompareFunc cmp, SwapFunc swap)
{
    int __r = __sort4(x1, x2, x3, x4, cmp);
    if (cmp(x5, x4) < 0)
    {
        swap(x4, x5);
        ++__r;
        if (cmp(x4, x3) < 0)
        {
            swap(x3, x4);
            ++__r;
            if (cmp(x3, x2) < 0)
            {
                swap(x2, x3);
                ++__r;
                if (cmp(x2, x1) < 0)
                {
                    swap(x1, x2);
                    ++__r;
                }
            }
        }
    }

    return __r;
}

int _small_sort(void* base, size_t nitems, size_t sizeElem, CompareFunc cmp, SwapFunc swap)
{
    int r = 0;
    void* x2;
    void* x3;
    void* x4;
    void* x5;

    switch(nitems)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            x2 = base + sizeElem;
            r = _sort2(base, x2, cmp, swap);
            break;
        case 3:
            x2 = base + sizeElem;
            x3 = x2+ sizeElem;
            r = _sort3(base, x2, x3, cmp, swap);
            break;
        case 4:
            x2 = base + sizeElem;
            x3 = x2 + sizeElem;
            x4 = x3 + sizeElem;
            r = _sort4(base, x2, x3, x4, cmp, swap);
            break;
        case 5:
            x2 = base + sizeElem;
            x3 = x2 + sizeElem;
            x4 = x3 + sizeElem;
            x5 = x4 + sizeElem;
            r = _sort5(base, x2, x3, x4, x5, cmp, swap);
            break;
        default:
            // call insertion sort
            
            break;
    }

    return r;    
}
*/

size_t _checksum(void* base, size_t nitems, size_t sizeElem)
{
    size_t sum = 0;
    uint8_t* ptr = (uint8_t*)base;

    for(size_t i = 0; i < nitems * sizeElem; i++)
    {
        sum += *ptr++;
    }

    return sum;
}
