// C Standred
#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// File Header
#include "util_vector.h"

VecInt_t VecIntAlloc(size_t cap)
{
    cap = VEC_INIT_CAP;

    VecInt_t vec = (VecInt_t)malloc(sizeof(*vec));
    if(vec == NULL)
        return NULL;

    vec->data = (int *)calloc(cap, sizeof(int));
    if(vec->data == NULL)
    {
        free(vec);
        return NULL;
    }

    vec->size           = 0;
    vec->cap            = cap;
    vec->flags.in_stack = false;

    return vec;
}

int VecIntFree(VecInt_t *vecPtr)
{
    if(vecPtr == NULL)
        return -1;

    VecInt_t vec = *vecPtr;
    if(vec->flags.in_stack)
        return -1;

    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->cap  = 0;

    free(vec);
    vecPtr = NULL;

    return 0;
}

int VecIntReserve(VecInt_t vec, size_t cap)
{
    if(vec->flags.in_stack)
        return -1;
    if(cap > vec->cap)
    {
        int *tempdata = (int *)realloc(vec->data, cap * sizeof(int));
        if(tempdata == NULL)
            return -1;
        vec->data = tempdata;
        vec->cap  = cap;
    }
    memset(vec->data + vec->size, 0, (vec->cap - vec->size) * sizeof(int));
    return 0;
}

int VecIntClear(VecInt_t vec)
{
    memset(vec->data, 0, vec->cap * sizeof(int));
    vec->size = 0;
    return 0;
}

int VecIntInsert(VecInt_t vec, size_t start, int elem)
{
    if(start > vec->size)
        return -1;
    if(vec->size + 1 > vec->cap && VecIntReserve(vec, VEC_GROW_CAP) != 0)
        return -1;
    memmove(vec->data + start + 1, vec->data + start, (vec->size - start) * sizeof(int));
    vec->data[start] = elem;
    vec->size++;
    return 0;
}

int VecIntErase(VecInt_t vec, size_t start)
{
    if(start > vec->size)
        return -1;
    else if(start == vec->size - 1)
        return VecIntPopBack(vec);
    else
    {
        memmove(vec->data + start, vec->data + start + 1, (vec->size - start - 1) * sizeof(int));
        vec->size--;
    }
    return 0;
}

int VecIntPushBack(VecInt_t vec, int elem)
{
    if(vec->size + 1 > vec->cap && VecIntReserve(vec, VEC_GROW_CAP) != 0)
        return -1;
    vec->data[vec->size] = elem;
    vec->size++;
    return 0;
}

int VecIntPopBack(VecInt_t vec)
{
    if(vec->size > 0)
        vec->size--;
    else
        return -1;
    return 0;
}

int VecIntResize(VecInt_t vec, size_t size)
{
    if(vec->flags.in_stack)
        return -1;
    if(VecIntReserve(vec, size) != 0)
        return -1;
    if(size < vec->size)
        memset(vec->data + size, 0, (vec->size - size) * sizeof(int));
    vec->size = size;
    return 0;
}

int VecIntFillElems(VecInt_t vec, size_t start, size_t num, const int elem)
{
    if(start > vec->size)
        return -1;
    const size_t size = vec->size + num - start - 1;
    if(size > vec->cap && VecIntResize(vec, size) != 0)
        return -1;
    for(size_t i = start; i < start + num; i++)
        memcpy(vec->data + i, &elem, sizeof(int));
    vec->size = size;
    return 0;
}

int VecIntInsertElems(VecInt_t vec, size_t start, size_t elemNum, ...)
{
    if(start > vec->size)
        return -1;
    if(vec->size + elemNum > vec->cap && VecIntReserve(vec, vec->size + elemNum) != 0)
        return -1;
    if(start != vec->size)
        memmove(vec->data + start + elemNum, vec->data + start, (vec->size - start) * sizeof(int));
    va_list elemList;
    va_start(elemList, elemNum);
    for(size_t i = start; i < start + elemNum; i++)
        vec->data[i] = (int)va_arg(elemList, int);
    va_end(elemList);
    vec->size += elemNum;
    return 0;
}
