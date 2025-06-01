#include "../include/utf8util.h"
#include <stdio.h>

void format_time_chr(char *dest, size_t size, char *src, unsigned long offset)
{
    unsigned int time = atoul(src);
    time += offset;
    snprintf(dest, size, "%02d:%02d", time/60, time%60);
}
