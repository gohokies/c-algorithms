#include <assert.h>

#include "insertionsort.h"
#include "sortcommon.h"

#define INSERTION_SORT(Type, Base, Items)                       \
    if(Items > 1){                                              \
        Type* it = (Type*)Base;                                 \
        it++;                                                   \
        for(size_t i = 1; i < Items; i++, it++){                \
            Type* cur = it;                                     \
            Type* cur_1 = it - 1;                               \
            if (*cur < *cur_1){                                 \
                Type v = *cur;                                  \
                do{                                             \
                    *cur-- = *cur_1;                            \
                }while(cur != (Type*)Base && v < *(--cur_1));   \
                *cur = v;                                       \
            }                                                   \
        }                                                       \
    }                                                           \

#define INSERTION_RSORT(Type, Base, Items)                      \
    if(Items > 1){                                              \
        Type* it = (Type*)Base;                                 \
        it++;                                                   \
        for(size_t i = 1; i < Items; i++, it++){                \
            Type* cur = it;                                     \
            Type* cur_1 = it - 1;                               \
            if (*cur > *cur_1){                                 \
                Type v = *cur;                                  \
                do{                                             \
                    *cur-- = *cur_1;                            \
                }while(cur != (Type*)Base && v > *(--cur_1));   \
                *cur = v;                                       \
            }                                                   \
        }                                                       \
    }                                                           \


#define INSERTION_SORT_COMPARE(Type, Base, Items, Cmp)          \
    if(Items > 1){                                              \
        Type* it = (Type*)Base;                                 \
        it++;                                                   \
        for(size_t i = 1; i < Items; i++, it++){                \
            Type* cur = it;                                     \
            Type* cur_1 = it - 1;                               \
            if (Cmp(cur, cur_1)){                               \
                Type v = *cur;                                  \
                do{                                             \
                    *cur-- = *cur_1;                            \
                }while(cur != (Type*)Base && cmp(&v, --cur_1)); \
                *cur = v;                                       \
            }                                                   \
        }                                                       \
    }                                                           \



static int insertion_sort_s4(void* base, size_t nitems, CompareFunc cmp)
{
    INSERTION_SORT_COMPARE(uint32_t, base, nitems, cmp);
    return 0;
}

static int insertion_sort_s8(void* base, size_t nitems, CompareFunc cmp)
{
    INSERTION_SORT_COMPARE(uint64_t, base, nitems, cmp);
    return 0;
}

int insertion_sort(void* base, size_t nItems, size_t sizeElem, CompareFunc cmp)
{
    int r = 0;
    uint8_t buffer[256];
    uint8_t* pBuffer = buffer;
    void* it = base;

    if (sizeElem == sizeof(uint32_t)){
        return insertion_sort_s4(base, nItems, cmp);
    }

    if (sizeElem == sizeof(uint64_t)){
        return insertion_sort_s8(base, nItems, cmp);
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

// Specialization for common types
int insertion_sort_uint32(uint32_t* base, size_t nitems)
{
    INSERTION_SORT(uint32_t, base, nitems);
    return 0;
}

int insertion_sort_uint64(uint64_t* base, size_t nitems)
{
    INSERTION_SORT(uint64_t, base, nitems);
    return 0;
}

int insertion_sort_float(float* base, size_t nitems)
{
    INSERTION_SORT(float, base, nitems);
    return 0;
}

int insertion_sort_double(double* base, size_t nitems)
{
    INSERTION_SORT(double, base, nitems);
    return 0;
}

// Specialization for sorting common types descendently
int insertion_rsort_uint32(uint32_t* base, size_t nitems)
{
    INSERTION_RSORT(uint32_t, base, nitems);
    return 0;
}

int insertion_rsort_uint64(uint64_t* base, size_t nitems)
{
    INSERTION_RSORT(uint64_t, base, nitems);
    return 0;
}

int insertion_rsort_float(float* base, size_t nitems)
{
    INSERTION_RSORT(float, base, nitems);
    return 0;
}

int insertion_rsort_double(double* base, size_t nitems)
{
    INSERTION_RSORT(double, base, nitems);
    return 0;
}