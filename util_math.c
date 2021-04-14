#include "util_math.h"

int UtilNumConv(struct Number *num, const char *str)
{
    // For example:
    // "100": INT = 100
    // "1e2": DBL = 100.000000
    // "0.01": DBL = 0.010000
    // "1e-2": DBL = 0.010000
    // "": ERROR: strlen = 0
    // "2147483648": ERROR: out of range
    // "1.8E+308": ERROR: out of range
    // "1ee2": ERROR: illegal

    num->type = NUM_TYPE_ERR;
    num->value.i = 0;

    if (strlen(str) == 0)
    {
        num->type = NUM_TYPE_ERR;
        return UTIL_FAIL;
    }

    if (!strcmp("+oo", str))
    {
        num->type = NUM_TYPE_P_INF;
        return UTIL_PASS;
    }

    if (!strcmp("-oo", str))
    {
        num->type = NUM_TYPE_N_INF;
        return UTIL_PASS;
    }

    char *intEnd = NULL;
    int intRs = strtol(str, &intEnd, 0);
    if (errno != 0)
    {
        num->type = NUM_TYPE_ERR;
        return UTIL_FAIL;
    }
    if (*intEnd == '\0')
    {
        num->type = NUM_TYPE_INT;
        num->value.i = intRs;
        return UTIL_PASS;
    }

    char *dblEnd = NULL;
    double dblRs = strtod(str, &dblEnd);
    if (errno != 0)
    {
        num->type = NUM_TYPE_ERR;
        return UTIL_FAIL;
    }
    if (*dblEnd == '\0')
    {
        num->type = NUM_TYPE_DBL;
        num->value.d = dblRs;
        return UTIL_PASS;
    }

    return UTIL_FAIL;
}

const char *UtilNumDump(char *str, const struct Number *num)
{

    switch (num->type)
    {
    case NUM_TYPE_INT:
        sprintf(str, "%d", num->value.i);
        return str;
    case NUM_TYPE_DBL:
        sprintf(str, "%f", num->value.d);
        return str;
    case NUM_TYPE_N_INF:
        return "-oo";
    case NUM_TYPE_P_INF:
        return "+oo";
    default:
        return "NUMBER TYPE ERROR";
    }
}

// clang-format off
bool UtilMathIntIntGt  (int a, int b){ return (a >  b); }
bool UtilMathIntIntGtEq(int a, int b){ return (a >= b); }
bool UtilMathIntIntEq  (int a, int b){ return (a == b); }
bool UtilMathIntIntLs  (int a, int b){ return (a <  b); }
bool UtilMathIntIntLsEq(int a, int b){ return (a <= b); }

bool UtilMathDblDblGt  (double a, double b){ return (a > b) && (fabs(a - b) >  UTIL_MATH_ESP); }
bool UtilMathDblDblGtEq(double a, double b){ return (a > b) || (fabs(a - b) <= UTIL_MATH_ESP); }
bool UtilMathDblDblEq  (double a, double b){ return            (fabs(a - b) <= UTIL_MATH_ESP); }
bool UtilMathDblDblLsEq(double a, double b){ return (a < b) || (fabs(a - b) <= UTIL_MATH_ESP); }
bool UtilMathDblDblLs  (double a, double b){ return (a < b) && (fabs(a - b) >  UTIL_MATH_ESP); }

bool UtilMathIntDblGt  (int a, double b){ return UtilMathDblDblGt  ((double)a, b); }
bool UtilMathIntDblGtEq(int a, double b){ return UtilMathDblDblGtEq((double)a, b); }
bool UtilMathIntDblEq  (int a, double b){ return UtilMathDblDblEq  ((double)a, b); }
bool UtilMathIntDblLsEq(int a, double b){ return UtilMathDblDblLsEq((double)a, b); }
bool UtilMathIntDblLs  (int a, double b){ return UtilMathDblDblLs  ((double)a, b); }

bool UtilMathDblIntGt  (double a, int b){ return UtilMathDblDblGt  (a, (double)b); }
bool UtilMathDblIntGtEq(double a, int b){ return UtilMathDblDblGtEq(a, (double)b); }
bool UtilMathDblIntEq  (double a, int b){ return UtilMathDblDblEq  (a, (double)b); }
bool UtilMathDblIntLsEq(double a, int b){ return UtilMathDblDblLsEq(a, (double)b); }
bool UtilMathDblIntLs  (double a, int b){ return UtilMathDblDblLs  (a, (double)b); }
// clang-format on
