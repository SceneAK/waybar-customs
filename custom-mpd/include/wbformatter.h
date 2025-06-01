#ifndef WBFORMATTER_H
#define WBFORMATTER_H
#include <stddef.h>

size_t populate_format(char *buf, size_t buf_size, 
                       struct KeyValPtr *kvptrs, size_t kvptrs_len, 
                       char *fmt);

void print_waybarf(char *text, char *tooltip, char *cls);

#endif
