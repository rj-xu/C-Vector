#pragma once

#include "util_define.h"

extern size_t UtilStrSplite(char *buf, const char *str,
                            const char *delim, char *tokenList[]);

extern void UtilStrReverse(char *buf, const char *str);

extern char *UtilStrStrip(char *buf, const char *str, const char charList[]);
extern char *UtilStrStripLeft(char *buf, const char *str, const char charList[]);
extern char *UtilStrStripRight(char *buf, const char *str, const char charList[]);

extern bool UtilStrInclude(const char *str, const char charList[]);
extern bool UtilStrExclude(const char *str, const char charList[]);

extern size_t UtilStrCount(const char *str, const char charList[], size_t countList[]);
extern size_t UtilStrRemove(const char *str, const char charList[], size_t countList[]);
extern size_t UtilStrReplace(char *buf, const char *str, const char charList[], size_t countList[], const char replace);
