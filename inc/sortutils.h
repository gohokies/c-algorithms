#ifndef _SORTUTILS_H_
#define _SORTUTILS_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __plusplus
extern "C"
{
#endif

typedef enum _swap_type
{
    Raw = 0,
    Align
} swap_type;


static inline void basic_move(void* dst, void* src, size_t size)
{
    memcpy(dst, src, size);
}

static inline void basic_swap(void* l, void* r, size_t size)
{
    uint8_t* pl = (uint8_t *)l;
    uint8_t* pr = (uint8_t *)r;
    while (size > 0)
    {
        uint8_t v = *pl;
        *pl++ = *pr;
        *pr++ = v;
        size--;
    }
}

static inline void align_swap(void* l, void* r, size_t size)
{ 
    size_t* pl = (size_t*)l;
    size_t* pr = (size_t*)r;
    while (size >= sizeof(size_t))
    {
        size_t v = *pl;
        *pl++ = *pr;
        *pr++ = v;
        size -= sizeof(size_t);   
    }
}

static inline void adv_swap(void* l, void* r, size_t size, swap_type type)
{
    switch(type)
    {
        case Raw:
            {
                uint8_t* pl = (uint8_t *)l;
                uint8_t* pr = (uint8_t *)r;
                while (size > 0)
                {
                    uint8_t v = *pl;
                    *pl++ = *pr;
                    *pr++ = v;
                    size--;
                }
            }
            break;
        case Align:
            {
                size_t* pl = (size_t*)l;
                size_t* pr = (size_t*)r;
                while (size >= sizeof(size_t))
                {
                    size_t v = *pl;
                    *pl++ = *pr;
                    *pr++ = v;
                    size -= sizeof(size_t);   
                }
            }
            break;
        default:
            break;
    }
}

#ifdef __plusplus
}
#endif

#endif