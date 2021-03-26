#include "util_interval.h"

enum EpType
{
    EP_TYPE_N_INF,
    EP_TYPE_P_INF,
    EP_TYPE_INT,
    EP_TYPE_DBL,
};

union EpValue
{
    int i;
    double d;
};

struct Endpoint
{
    enum EpType type;
    union EpValue value;
    bool isOpen;
};

struct Interval
{
    struct Endpoint left;
    struct Endpoint right;
};

static bool UtilItvIsLegallLimit(const char *limit)
{

}
