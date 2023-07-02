#include <stdint.h>

#include "sortutils.h"

void basic_move(void* dst, void* src, size_t size)
{
    memcpy(dst, src, size);
}

void basic_swap(void* l, void* r, size_t size)
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

void align_swap(void* l, void* r, size_t size)
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
