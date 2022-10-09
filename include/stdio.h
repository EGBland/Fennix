#ifndef __STDIO_H_DEFINED
#define __STDIO_H_DEFINED 1

#include <stdarg.h>

int _sprintf(char *buf, const char *format, va_list lst);
int sprintf(char *buf, const char *format, ...);
void memcpy(char *dst, char *src, unsigned int len);

#endif