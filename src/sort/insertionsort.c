#include <assert.h>

#include "insertionsort.h"
#include "sortcommon.h"

// Sorts [begin, end) using insertion sort with the given comparison function.
static int insertion_sort_s4(void* base, size_t nItems, size_t sizeElem, CompareFunc cmp)
{
    int r = 0;
    uint8_t* it = (uint8_t*)base;

    if (nItems < 2) return r;

    it += sizeElem;
    for (size_t i = 1; i < nItems; i++) 
    {
        uint8_t* cur = it;
        uint8_t* cur_1 = it - sizeElem;

        // Compare first to avoid 2 moves for an element already positioned correctly.
        if (cmp(cur, cur_1))
        {
            uint32_t v;

            v = *(uint32_t*)cur;
            do
            { 
                *(uint32_t*)cur = *(uint32_t*)cur_1;

                cur -= sizeElem;
                cur_1 -= sizeElem;
            }
            while(cur != base && cmp(&v, cur_1));

            *(uint32_t*)cur = v;
        }

        it += sizeElem;
    }

    return 0;
}

// Sorts [begin, end) using insertion sort with the given comparison function.
int insertion_sort(void* base, size_t nItems, size_t sizeElem, CompareFunc cmp)
{
    int r = 0;
    uint8_t buffer[256];
    uint8_t* pBuffer = buffer;
    void* it = base;

    if (sizeElem == sizeof(uint32_t)){
        return insertion_sort_s4(base, nItems, sizeElem, cmp);
    }

    if (nItems < 2) return r;
    if (sizeElem > sizeof(buffer))
    {
        pBuffer = malloc(sizeElem);
        if (pBuffer == NULL) return -1;
    }

    it += sizeElem;
    for (size_t i = 1; i < nItems; i++) 
    {
        void* cur = it;
        void* cur_1 = it - sizeElem;

        // Compare first to avoid 2 moves for an element already positioned correctly.
        if (cmp(cur, cur_1))
        {
            memcpy(pBuffer, cur, sizeElem);
            
            do
            { 
                memcpy(cur, cur_1, sizeElem);

                cur -= sizeElem;
                cur_1 -= sizeElem;
            }
            while(cur != base && cmp(buffer, cur_1));

            memcpy(cur, pBuffer, sizeElem);
        }

        it += sizeElem;
    }

    if (pBuffer != buffer) free(pBuffer);

    return 0;
}