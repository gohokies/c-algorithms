#include "insertionsort.h"
#include "sortcommon.h"

// Sorts [begin, end) using insertion sort with the given comparison function.
int insertion_sort(void* base, size_t nItems, size_t sizeElem, CompareFunc cmp, MoveFunc mv)
{
    int r = 0;
    uint8_t buffer[256];
    uint8_t* pBuffer = buffer;
    void* it = base;


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
        if (cmp(cur, cur_1) < 0)
        {
            mv(pBuffer, cur, sizeElem);
            r++;
            
            do
            { 
                mv(cur, cur_1, sizeElem);
                r++;
                cur -= sizeElem;
                cur_1 -= sizeElem;
            }
            while(cur != base && cmp(buffer, cur_1) < 0);

            mv(cur, pBuffer, sizeElem);
            r++;
        }

        it += sizeElem;
    }

    if (pBuffer != buffer) free(pBuffer);

    return 0;
}