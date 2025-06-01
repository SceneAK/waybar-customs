#include "../include/keyval.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

ssize_t kv_index_of(const char *key, struct KeyValPtr *kvptrs, size_t len)
{
    ssize_t i;
    for(i = 0; i < len; i++)
    {
        if(strcmp(key, kvptrs[i].key) == 0){
            return i;
        }
    }
    return -1;
}

char *kv_val_of(const char *key, struct KeyValPtr *kvptrs, size_t len)
{
    ssize_t index = kv_index_of(key, kvptrs, len);
    if(index == -1){
        return NULL;
    }
    return kvptrs[index].val;
}

void kv_insert_sort_desc(struct KeyValPtr *kvptrs, size_t len)
{
    /* ChatGPT _Inspired_ */
    struct KeyValPtr tmp;
    size_t i;
    size_t j;

    for (i = 1; i < len; ++i) {
        tmp = kvptrs[i];
        j = i;
        while (j > 0 && strlen(kvptrs[j-1].key) < strlen(tmp.key)) {
            kvptrs[j] = kvptrs[j-1];
            --j;
        }
        kvptrs[j] = tmp;
    }
}

void kv_testprint(struct KeyValPtr *kvptrs, size_t len)
{
    size_t i;
    printf("Printing Key value with length %lu\n", len);
    for(i = 0; i < len; i++)
    {
        printf("%lu. KEY:%s, VAL:%s\n", i+1, kvptrs[i].key, kvptrs[i].val);
    }
}
