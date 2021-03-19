#pragma once

// Util Define
#include "./util_define.h"

// Maximum bytes of vector in stack
#define VEC_STACK_MAX (10000)
// Initial capacity of vector
#define VEC_INIT_CAP (cap > 0 ? cap : 1)
// Grown capacity of vector
#define VEC_GROW_CAP (vec->cap > 0 ? vec->cap * 2 : 1)

/**
 * @brief Constructor for vector in stack
 * 
 */
#define VEC(VecType_t, cap)                                                     \
    ({                                                                          \
        VecType_t _vec      = NULL;                                             \
        size_t    _cap      = (size_t)(cap);                                    \
        size_t    _byteSize = sizeof(*_vec) + _cap * sizeof(_vec->data[0]);     \
                                                                                \
        _vec = _byteSize > VEC_STACK_MAX ? NULL : (VecType_t)alloca(_byteSize); \
        if(_vec != NULL)                                                        \
        {                                                                       \
            _vec->data = (typeof(_vec->data))((char *)_vec + sizeof(*_vec));    \
            memset(_vec->data, 0, _cap * sizeof(_vec->data[0]));                \
                                                                                \
            _vec->size           = 0;                                           \
            _vec->cap            = _cap;                                        \
            _vec->flags.in_stack = true;                                        \
        }                                                                       \
        _vec;                                                                   \
    })

// Vector<int>
typedef struct
{
    size_t size;
    size_t cap;
    union
    {
        uint8_t raw;
        struct
        {
            uint8_t in_stack : 1;
            uint8_t refuse_mod : 1;
        };
    } flags;
    int *data;
} * VecInt_t;

/**
 * @brief Constructor for vector in heap
 * 
 * @param cap 
 * @return VecInt_t 0 for PASS, others for FAIL.
 */
VecInt_t VecIntAlloc(size_t cap);

/**
 * @brief Destructor for vector in stack
 * 
 * @param vecPtr 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntFree(VecInt_t *vecPtr);

/**
 * @brief Reserves storage
 * 
 * @param vec 
 * @param cap 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntReserve(VecInt_t vec, size_t cap);

/**
 * @brief Clears the contents
 * 
 * @param vec 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntClear(VecInt_t vec);

/**
 * @brief Inserts an element
 * 
 * @param vec 
 * @param start 
 * @param elem 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntInsert(VecInt_t vec, size_t start, int elem);

/**
 * @brief Erases an element
 * 
 * @param vec 
 * @param start 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntErase(VecInt_t vec, size_t start);

/**
 * @brief Adds an element to the end
 * 
 * @param vec 
 * @param elem 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntPushBack(VecInt_t vec, int elem);

/**
 * @brief Removes the last element
 * 
 * @param vec 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntPopBack(VecInt_t vec);

/**
 * @brief Changes the number of elements stored
 * 
 * @param vec 
 * @param size 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntResize(VecInt_t vec, size_t size);

/**
 * @brief Fills [start, start+elemNum) elements with specific element
 * 
 * @param vec 
 * @param start 
 * @param elemNum 
 * @param elem 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntFillElems(VecInt_t vec, size_t start, size_t num, const int elem);

/**
 * @brief Inserts elements
 * 
 * @param vec 
 * @param start 
 * @param elemNum 
 * @param ... 
 * @return int 0 for PASS, others for FAIL.
 */
int VecIntInsertElems(VecInt_t vec, size_t start, size_t elemNum, ...);

// int VecEraseElems(VecInt_t vec, size_t start, size_t num);
// int VecIntFind(VecInt_t vec, VecInt_t elemList, const int elem);
// int VecIntSort(VecInt_t vec, VecInt_t elemList);
// int VecIntEqual(VecInt_t vec1, VecInt_t vec2)
