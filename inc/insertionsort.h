#ifndef _INSERTIONSORT_H_
#define _INSERTIONSORT_H_

#pragma once

#include "sortbase.h"

#ifdef __cplusplus
extern "C"
{
#endif

int insertion_sort(void* base, size_t nitems, size_t size, CompareFunc cmp);

int insertion_sort_uint32(uint32_t* base, size_t nitems);
int insertion_sort_uint64(uint64_t* base, size_t nitems);
int insertion_sort_float(float* base, size_t nitems);
int insertion_sort_double(double* base, size_t nitems);
int insertion_sort_string(char** base, size_t nitems);
int insertion_sort_wstring(wchar_t** base, size_t nitems);

int insertion_rsort_uint32(uint32_t* base, size_t nitems);
int insertion_rsort_uint64(uint64_t* base, size_t nitems);
int insertion_rsort_float(float* base, size_t nitems);
int insertion_rsort_double(double* base, size_t nitems);
int insertion_rsort_string(char** base, size_t nitems);
int insertion_rsort_wstring(wchar_t** base, size_t nitems);

#ifdef __cplusplus
}
#endif

#endif