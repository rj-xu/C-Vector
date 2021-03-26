#include "util_math.h"

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
