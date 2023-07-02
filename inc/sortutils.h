#ifndef _SORTUTILS_H_
#define _SORTUTILS_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __plusplus
extern "C"
{
#endif

void basic_move(void* dst, void* src, size_t size);

void basic_swap(void* l, void* r, size_t sizea);

void align_swap(void* l, void* r, size_t size);

#ifdef __plusplus
}
#endif

#endif