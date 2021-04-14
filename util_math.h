#pragma once

#include "util_define.h"

enum NumType
{
    NUM_TYPE_ERR = -1,
    NUM_TYPE_INT,
    NUM_TYPE_DBL,
    NUM_TYPE_N_INF,
    NUM_TYPE_P_INF,
};

struct Number
{
    enum NumType type;
    union
    {
        int i;
        double d;
    } value;
};

#define UTIL_MATH_ESP (1e-6)

extern int UtilNumConv(struct Number *num, const char *str);
extern const char *UtilNumDump(char *str, const struct Number *num);

// clang-format off
extern bool UtilMathIntIntGt  (int a, int b);
extern bool UtilMathIntIntGtEq(int a, int b);
extern bool UtilMathIntIntEq  (int a, int b);
extern bool UtilMathIntIntLs  (int a, int b);
extern bool UtilMathIntIntLsEq(int a, int b);

extern bool UtilMathDblDblGt  (double a, double b);
extern bool UtilMathDblDblGtEq(double a, double b);
extern bool UtilMathDblDblEq  (double a, double b);
extern bool UtilMathDblDblLsEq(double a, double b);
extern bool UtilMathDblDblLs  (double a, double b);


extern bool UtilMathIntDblGt  (int a, double b);
extern bool UtilMathIntDblGtEq(int a, double b);
extern bool UtilMathIntDblEq  (int a, double b);
extern bool UtilMathIntDblLsEq(int a, double b);
extern bool UtilMathIntDblLs  (int a, double b);

extern bool UtilMathDblIntGt  (double a, int b);
extern bool UtilMathDblIntGtEq(double a, int b);
extern bool UtilMathDblIntEq  (double a, int b);
extern bool UtilMathDblIntLsEq(double a, int b);
extern bool UtilMathDblIntLs  (double a, int b);
// clang-format on
