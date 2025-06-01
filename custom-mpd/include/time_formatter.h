#ifndef TIME_FORMATTER_H
#define TIME_FORMATTER_H

#include <stddef.h>
#define TIME_BUF_SIZE 8

void format_time_chr(char *dest, size_t size, char *src, unsigned long offset);

#endif
