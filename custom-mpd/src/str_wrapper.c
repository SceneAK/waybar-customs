#include "../include/utf8util.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

void wrap_str_n(char *dest, const char *src, size_t n, size_t offset)
{
    size_t src_len = strlen(src);
    size_t i;

    for(i = 0; i < src_len && i < n-1; i++)
    {
        dest[i] = src[ (offset + i) % src_len ];
    }
    dest[n] = '\0';
}

void wrapcpy_utf8str(char *dest, const char *src, size_t cpylen, size_t max_bytes, size_t offset)
{
    size_t i;
    size_t src_len = strlen(src);
    size_t current_len = 0;
    src = get_utf8chr_of_index(src, offset);
      
    for(i = 0; current_len < cpylen+1 && i < max_bytes-1; i++, src++)
    {
        if(*src == '\0'){
            src -= src_len;
        }
        dest[i] = *src;

        if(get_num_bytes((unsigned char)*src) != -1){ /* Is not continuation chr, it's a code point */
            current_len++;
        }
    }
    dest[i-1] = '\0';
}
/* 
 * Add missing kv a value (Just add the basic ones bro)
 * Fix issue with json parsing controll characters (", \n, \t, etc)
 * */
