#include <stddef.h>
#include <string.h>

void scroll(char *str, unsigned int offset)
{
    char    first = *str;
    size_t  len = strlen(str);
    size_t  i, x;
     
    for(i = 0; i < len; i++)
    {
        x = (i + offset) % len;
        str[i] = str[ x == 0 ? first : x ];
    }
}
