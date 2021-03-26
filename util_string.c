#include "util_string.h"

size_t UtilStrSplite(char *const buf, const char *const str,
                     const char *const delim, char *tokenList[])
{
    const bool isSameDestSrc = (buf == str);
    const bool needOutput = (tokenList != NULL);

    if (!isSameDestSrc)
        strcpy(buf, str);

    size_t i = 0;
    char *rest = buf;
    char *token = NULL;

    while ((token = strtok_r(rest, delim, &rest)))
    {
        if (needOutput)
            tokenList[i++] = token;
    }

    return i;
}

void UtilStrReverse(char *const buf, const char *const str)
{
    const size_t len = strlen(str);

    for (size_t i = 0; i < len / 2; i++)
    {
        // keep c for same dest src
        char c = *(str + i);
        *(buf + i) = *(str + len - 1 - i);
        *(buf + len - 1 - i) = c;
    }
}

char *UtilStrStripLeft(char *buf, const char *str, const char charList[])
{
    const size_t len = strlen(str);
    const size_t charNum = strlen(charList);

    size_t start = 0;
    for (; start < len; start++)
    {
        size_t j = 0;
        while (j < charNum && str[start] != charList[j])
            j++;
        if (j == charNum)
            break;
    }

    // Won't memory overlap even same dest src
    // +1 for copying NOP
    memcpy(buf, str + start, len - start + 1);

    return str + start;
}

char *UtilStrStripRight(char *buf, const char *str, const char charList[])
{
    const size_t len = strlen(str);
    const size_t charNum = strlen(charList);

    size_t end = len - 1;
    for (; end > -1; end--)
    {
        size_t j = 0;
        while (j < charNum && str[end] != charList[j])
            j++;
        if (j == charNum)
            break;
    }

    if (buf != str)
        memcpy(buf, str, end);
    buf[end + 1] = '\0';

    return str + end;
}

char *UtilStrStrip(char *buf, const char *str, const char charList[])
{
    const size_t len = strlen(str);
    const size_t charNum = strlen(charList);

    size_t end = len - 1;
    for (; end > -1; end--)
    {
        size_t j = 0;
        while (str[end] != charList[j] && j < charNum)
            j++;
        if (j == charNum)
            break;
    }

    size_t start = 0;
    for (; start < end; start++)
    {
        size_t j = 0;
        while (str[start] != charList[j] && j < charNum)
            j++;
        if (j == charNum)
            break;
    }

    memcpy(buf, str + start, end - start + 1);
    buf[end + 1] = '\0';

    return str + start;
}
