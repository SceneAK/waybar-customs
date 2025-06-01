#ifndef KEYVAL_H
#define KEYVAL_H
#include <stddef.h>
#include <sys/types.h>

#define KV_ADD(arg_key, arg_val, kvptrs, len) do { (kvptrs)[(len)].key = (arg_key); (kvptrs)[(len)].val = (arg_val); (len)++; } while(0)

struct KeyValPtr
{
    char *key;
    char *val;
};
void kv_insert_sort_desc(struct KeyValPtr *kvptrs, size_t len);

ssize_t kv_index_of(const char *key, struct KeyValPtr *kvptrs, const size_t len);

char *kv_val_of(const char *key, struct KeyValPtr *kvptrs, const size_t len);

void kv_testprint(struct KeyValPtr *kvptrs, size_t len);

#endif
