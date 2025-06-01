#ifndef FMTTED_TIME_KVS_H
#define FMTTED_TIME_KVS_H
#define FMT_SIZE 8
#include <stddef.h>
struct _fmtted_time{
  /*unsigned int    elapsed;
    unsigned int    duration;*/
    char            elapsed_fmtted[FMT_SIZE];
    char            duration_fmtted[FMT_SIZE];
};

void fmtted_time_update(struct _fmtted_time *formatted, struct KeyValPtr *mpd_kvptrs, size_t len, unsigned long elapsed_off_s);

size_t fmtted_time_kvs_add(struct _fmtted_time *dest_fmtted, struct KeyValPtr *mpd_kvptrs, size_t size, size_t len);


#endif
