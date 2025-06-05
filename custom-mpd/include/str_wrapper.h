#ifndef STR_WRAPPER_H
#define STR_WRAPPER_H

#include <stddef.h>

void wrapcpy_utf8str(char *dest, const char *src, size_t cpylen, size_t max_bytes, size_t utf8offset);

#endif
