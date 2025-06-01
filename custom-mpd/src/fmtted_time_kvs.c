#include "../include/time_formatter.h"
#include "../include/keyval.h"
#include "../include/fmtted_time_kvs.h"
#include <stdlib.h>
#include <stdio.h>

#define ELAPSED_FMTTED_KEY "elapsed_fmtted"
#define DURATION_FMTTED_KEY "duration_fmtted"

void fmtted_time_update(struct _fmtted_time *formatted, struct KeyValPtr *mpd_kvptrs, size_t len, unsigned long elapsed_off_s)
{
    char *elapsed_val = kv_val_of("elapsed", mpd_kvptrs, len);
    char *duration_val = kv_val_of("duration", mpd_kvptrs, len);
    
    if(elapsed_val == NULL || duration_val == NULL){
        return;
    }
    format_time_chr(formatted->elapsed_fmtted, sizeof(formatted->elapsed_fmtted), elapsed_val, elapsed_off_s);
    format_time_chr(formatted->duration_fmtted, sizeof(formatted->duration_fmtted), duration_val, 0);
}

size_t fmtted_time_kvs_add(struct _fmtted_time *dest_fmtted, struct KeyValPtr *mpd_kvptrs, size_t size, size_t len)
{
    if(len + 2 >= size){
        fprintf(stderr, "Not enough space for fmtted_time_kvs");
        return len;
    }
    KV_ADD(ELAPSED_FMTTED_KEY, dest_fmtted->elapsed_fmtted, mpd_kvptrs, len);
    KV_ADD(DURATION_FMTTED_KEY, dest_fmtted->duration_fmtted, mpd_kvptrs, len);
    fmtted_time_update(dest_fmtted, mpd_kvptrs, len, 0);
    return len;
}
