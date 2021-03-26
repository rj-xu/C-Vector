#include "util_time.h"

int UtilSysGetTimeStamp(char *const timeStamp, const size_t maxSize, const char *const fmt)
{
    time_t     utcTime   = time(NULL);
    struct tm *localTime = NULL;

    time(&utcTime);
    localTime = localtime(&utcTime);

    if(fmt == NULL)
        strftime(timeStamp, maxSize, "%Y%m%d%H%M%S", localTime);
    else
        strftime(timeStamp, maxSize, fmt, localTime);

    return UTIL_PASS;
}
