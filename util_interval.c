#include "util_define.h"

#include "util_string.h"
#include "util_math.h"

#include "util_interval.h"

struct Endpoint
{
    struct Number num;
    bool isOpen;
};

struct Interval
{
    struct Endpoint left;
    struct Endpoint right;
};

#define UTIL_INR_CHECK_ENDPOINT(IntDbl, int_dbl, LeftRightOpenClose, left_right, Op, NP_INF) \
    static bool UtilInrCheck##IntDbl##Endpoint##LeftRightOpenClose(                          \
        const int_dbl val, const struct Interval *inr)                                       \
    {                                                                                        \
        switch (inr->left_right.num.type)                                                    \
        {                                                                                    \
        case NUM_TYPE_INT:                                                                   \
            return UtilMath##IntDbl##Int##Op(val, inr->left_right.num.value.i);              \
        case NUM_TYPE_DBL:                                                                   \
            return UtilMath##IntDbl##Dbl##Op(val, inr->left_right.num.value.d);              \
        case NP_INF:                                                                         \
            return true;                                                                     \
        default:                                                                             \
            return false;                                                                    \
        }                                                                                    \
    }

UTIL_INR_CHECK_ENDPOINT(Int, int, LeftOpen, left, Gt, NUM_TYPE_N_INF)
UTIL_INR_CHECK_ENDPOINT(Int, int, LeftClose, left, GtEq, NUM_TYPE_N_INF)
UTIL_INR_CHECK_ENDPOINT(Int, int, RightOpen, right, Ls, NUM_TYPE_P_INF)
UTIL_INR_CHECK_ENDPOINT(Int, int, RightClose, right, LsEq, NUM_TYPE_P_INF)

UTIL_INR_CHECK_ENDPOINT(Dbl, double, LeftOpen, left, Gt, NUM_TYPE_N_INF)
UTIL_INR_CHECK_ENDPOINT(Dbl, double, LeftClose, left, GtEq, NUM_TYPE_N_INF)
UTIL_INR_CHECK_ENDPOINT(Dbl, double, RightOpen, right, Ls, NUM_TYPE_P_INF)
UTIL_INR_CHECK_ENDPOINT(Dbl, double, RightClose, right, LsEq, NUM_TYPE_P_INF)

#undef UTIL_INR_CHECK_ENDPOINT

#define UTIL_INR_CHECK_IN_LIMIT(IntDbl, int_dbl)                                        \
    static bool UtilInrCheck##IntDbl##In(const int_dbl val, const struct Interval *inr) \
    {                                                                                   \
        const bool isLeftOpen = inr->left.isOpen;                                       \
        const bool isRightOpen = inr->right.isOpen;                                     \
        if (isLeftOpen && isRightOpen)                                                  \
            return (UtilInrCheck##IntDbl##EndpointLeftOpen(val, inr) &&                 \
                    UtilInrCheck##IntDbl##EndpointRightOpen(val, inr));                 \
        else if (isLeftOpen && !isRightOpen)                                            \
            return (UtilInrCheck##IntDbl##EndpointLeftOpen(val, inr) &&                 \
                    UtilInrCheck##IntDbl##EndpointRightClose(val, inr));                \
        else if (!isLeftOpen && isRightOpen)                                            \
            return (UtilInrCheck##IntDbl##EndpointLeftClose(val, inr) &&                \
                    UtilInrCheck##IntDbl##EndpointRightOpen(val, inr));                 \
        else if (!isLeftOpen && !isRightOpen)                                           \
            return (UtilInrCheck##IntDbl##EndpointLeftClose(val, inr) &&                \
                    UtilInrCheck##IntDbl##EndpointRightClose(val, inr));                \
        else                                                                            \
            return false;                                                               \
    }
UTIL_INR_CHECK_IN_LIMIT(Int, int)
UTIL_INR_CHECK_IN_LIMIT(Dbl, double)
#undef UTIL_INR_CHECK_IN_LIMIT

static int UtilInrConv(struct Interval *inr, const char *limit)
{
    const size_t n = strlen(limit);

    const char leftBracket = limit[0];
    const char rightBracket = limit[n - 1];

    switch (leftBracket)
    {
    case '(':
        inr->left.isOpen = true;
        break;
    case '[':
        inr->left.isOpen = false;
        break;
    default:
        return UTIL_FAIL;
    }

    switch (rightBracket)
    {
    case ')':
        inr->right.isOpen = true;
        break;
    case ']':
        inr->right.isOpen = false;
        break;
    default:
        return UTIL_FAIL;
    }

    char *buf = (char *)calloc(n + 1, sizeof(char));
    char **tokenList = (char **)calloc(n / 2 + 1, sizeof(char *));
    const int tokenNum = UtilStrSplite(buf, limit, ", ()[]", tokenList);

    if (tokenNum != 2)
        return UTIL_FAIL;

    if (UtilNumConv(&inr->left.num, tokenList[0]) != UTIL_PASS)
        return UTIL_FAIL;

    if (UtilNumConv(&inr->right.num, tokenList[1]) != UTIL_PASS)
        return UTIL_FAIL;

    if ((inr->left.num.type == NUM_TYPE_N_INF && inr->left.isOpen == false) ||
        (inr->left.num.type == NUM_TYPE_P_INF))
        return UTIL_FAIL;

    if ((inr->right.num.type == NUM_TYPE_P_INF && inr->right.isOpen == false) ||
        (inr->right.num.type == NUM_TYPE_N_INF))
        return UTIL_FAIL;
    
    return UTIL_PASS;
}

char *UtilInrDump(char *const str, const struct Interval limit)
{
    // sprintf(str, "%c%s, %s%c", leftBracket, leftValue, rightValue, rightBracket);
    return str;
}

bool UtilInrIntInLimit(const int val, const char *limit)
{
    struct Interval inr = {0};
    if (UtilInrConv(&inr, limit) != UTIL_PASS)
        return false;
    return UtilInrCheckIntIn(val, &inr);
}

bool UtilInrDblInLimit(const double val, const char *limit)
{
    struct Interval inr = {0};
    if (UtilInrConv(&inr, limit) != UTIL_PASS)
        return false;

    return UtilInrCheckDblIn(val, &inr);
}
