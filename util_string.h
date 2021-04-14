#pragma once

#include "util_define.h"

extern int UtilStrSplite(char *buf, const char *str,
                         const char *delim, char *tokenList[]);

extern char *UtilStrReverse(char *buf, const char *str);

extern char *UtilStrStrip(char *buf, const char *str, const char charList[]);
extern char *UtilStrStripLeft(char *buf, const char *str, const char charList[]);
extern char *UtilStrStripRight(char *buf, const char *str, const char charList[]);
