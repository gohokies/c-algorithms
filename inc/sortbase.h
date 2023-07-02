#ifndef _SORTBASE_H_
#define _SORTBASE_H_

#include <stdlib.h>

typedef int (*CompareFunc)(const void* l, const void* ri);
typedef void (*SwapFunc)(void* l, void* r, size_t size);
typedef void (*MoveFunc)(void* dst, void* src, size_t size);
#endif