#include "../include/utf8util.h"
#include <stddef.h>
#include <stdio.h>

unsigned int atoul(const char *s)
{
    /* ChatGPT Generated */
    unsigned int n = 0;
    while (*s >= '0' && *s <= '9') {
        n = n * 10 + (*s++ - '0');
    }
    return n;
}

/* should be inlined */
short get_num_bytes(unsigned char uchr)
{
    if(uchr < CONTINUATION_BITS){
        return 1;
    }else if( (uchr & FIRST_THREE_BITS) == TWO_BYTES_CHAR ){
        return 2;
    }else if( (uchr & FIRST_FOUR_BITS) == THREE_BYTES_CHAR ){
        return 3;
    }else if( (uchr & FIRST_FIVE_BITS) == FOUR_BYTES_CHAR ){
        return 4;
    }else{
        return -1;
    }
}

size_t utf8_strlen(const char *str)
{
    size_t len = 0;
    for(; *str != '\0';)
    {
        len++;
        str += get_num_bytes((unsigned char)*str);
    }
    return len;
}

const char *get_utf8chr_of_index(const char *str, size_t i)
{
    size_t current_i;
    for(current_i = 0; current_i < i; current_i++)
    {
        str += get_num_bytes((unsigned char)*str);
    }
    return str;
}
