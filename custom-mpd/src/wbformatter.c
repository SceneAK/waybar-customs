#include <stdio.h>
#include <string.h>
#include "../include/keyval.h"
#include "../include/wbformatter.h"

#define MIN(a, b) (a < b ? a : b)

size_t populate_format(char *buf, size_t buf_size, 
                       struct KeyValPtr *kvptrs, size_t kvptrs_len, 
                       char *fmt)
{
    size_t i, j;
    size_t buf_len = 0;
    size_t fmt_len = strlen(fmt);
    size_t key_len, val_len, cpy_len;

    for(i = 0; i < fmt_len && buf_len < buf_size;)
    {
        if(fmt[i] == '$'){
            i++;
            for(j = 0; j < kvptrs_len; j++)
            {
                key_len = strlen(kvptrs[j].key);
                if(strncmp(fmt + i, kvptrs[j].key, key_len) == 0){
                    i += key_len;
                    
                    val_len = strlen(kvptrs[j].val);
                    cpy_len = MIN(val_len, buf_size - buf_len - 1);

                    memcpy(buf + buf_len, kvptrs[j].val, cpy_len);
                    buf_len += cpy_len;

                    break;
                }
            }
        }else {
            buf[buf_len] = fmt[i];
            buf_len++;
            i++;
        }
    }
    buf[buf_len] = '\0';
    return buf_len;
}

void print_waybarf(char *text, char *tooltip, char *cls)
{
    printf("{ \"text\": \"%s\", \"tooltip\": \"%s\", \"class\": \"%s\" }\n", text, tooltip, cls);
    fflush(stdout);
    return;
}
