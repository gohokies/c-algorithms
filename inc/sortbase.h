#ifndef _SORTBASE_H_
#define _SORTBASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef bool (*CompareFunc)(const void* l, const void* ri);
typedef int (*CompareFunc3Way)(const void* l, const void* ri);
typedef void (*SwapFunc)(void* l, void* r, size_t size);
typedef void (*MoveFunc)(void* dst, void* src, size_t size);

#endif