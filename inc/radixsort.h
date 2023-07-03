#ifndef _RADIXSORT_H_
#define _RADIXSORT_H_

#pragma once

#include "sortbase.h"

typedef enum _RadixiType
{
    t_uint8 = 0,
    t_int8,
    t_uint16,
    t_int16,
    t_uint32,
    t_int32,
    t_uint64,
    t_int64,
    t_float,
    t_double,
    t_string,
    t_wstring
} RadixType;

typedef uint8_t (*DigitFunc)(void* elem, size_t kth);

typedef struct _RadixKey
{
    uint32_t fixed_key_size;
    uint32_t digits_in_group;
    DigitFunc get_digit;
} RadixKey;

#ifdef __cplusplus
extern "C"
{
#endif

int radix_sort_type_array(void* base, size_t nItems, size_t sizeElem, RadixType type);
int radix_sort(void*base, size_t nitems, size_t sizeElem, RadixKey* key, CompareFunc compare);

#ifdef __cplusplus
}
#endif

#endif