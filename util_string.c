#include "util_string.h"

int UtilStrSplite(char *buf, const char *str,
                  const char *delim, char *tokenList[])
{
    const bool isSameDestSrc = (buf == str);
    const bool needOutput = (tokenList != NULL);

    if (!isSameDestSrc)
        strcpy(buf, str);

    int i = 0;
    char *rest = buf;
    char *token = NULL;

    while ((token = strtok_r(rest, delim, &rest)))
    {
        if (needOutput)
            tokenList[i++] = token;
    }

    return i;
}

char *UtilStrReverse(char *buf, const char *str)
{
    const int len = strlen(str);

    for (int i = 0; i < len / 2; i++)
    {
        // keep c for same dest src
        char c = *(str + i);
        *(buf + i) = *(str + len - 1 - i);
        *(buf + len - 1 - i) = c;
    }

    return buf;
}

char *UtilStrStripLeft(char *buf, const char *str, const char charList[])
{
    const int len = strlen(str);
    const int charNum = strlen(charList);

    int start = 0;
    for (; start < len; start++)
    {
        int j = 0;
        for (; j < charNum; j++)
            if (str[start] == charList[j])
                break;
        if (j == charNum)
            break;
    }

    // Won't memory overlap even same dest srcUL
    // +1 for copying NUL
    memcpy(buf, str + start, len - start + 1);

    return buf;
}

char *UtilStrStripRight(char *buf, const char *str, const char charList[])
{
    const int len = strlen(str);
    const int charNum = strlen(charList);

    int end = len - 1;
    for (; end > -1; end--)
    {
        int j = 0;
        for (; j < charNum; j++)
            if (str[end] == charList[j])
                break;
        if (j == charNum)
            break;
    }

    if (buf != str)
        memcpy(buf, str, end + 1);
    buf[end + 1] = '\0';

    return buf;
}

char *UtilStrStrip(char *buf, const char *str, const char charList[])
{
    const int len = strlen(str);
    const int charNum = strlen(charList);

    int end = len - 1;
    for (; end > -1; end--)
    {
        int j = 0;
        for (; j < charNum; j++)
            if (str[end] == charList[j])
                break;
        if (j == charNum)
            break;
    }

    int start = 0;
    for (; start < end; start++)
    {
        int j = 0;
        for (; j < charNum; j++)
            if (str[start] == charList[j])
                break;
        if (j == charNum)
            break;
    }

    memcpy(buf, str + start, end - start + 1);
    buf[end - start + 1] = '\0';

    return buf;
}
