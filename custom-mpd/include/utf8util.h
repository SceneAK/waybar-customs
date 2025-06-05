#ifndef UTF8UTIL_H
#define UTF8UTIL_H

#include <stddef.h>

#define FIRST_TWO_BITS 0xC0
#define FIRST_THREE_BITS 0xE0
#define FIRST_FOUR_BITS 0xF0
#define FIRST_FIVE_BITS 0xF8

#define CONTINUATION_BITS 0x80
#define TWO_BYTES_CHAR 0xC0
#define THREE_BYTES_CHAR 0xE0
#define FOUR_BYTES_CHAR 0xF0

short get_num_bytes(unsigned char chr);

unsigned int atoul(const char *s);

size_t utf8_strlen(const char *str);

const char *get_utf8chr_of_index(const char *str, size_t i);


#endif
