#include "../include/keyval.h"
#include <string.h>
#include <stdio.h>

size_t titlefilename_kv_add(struct KeyValPtr *mpd_kvptrs, size_t size, size_t len)
{
    char *file;
    char *title;
    char *filename_unix;
    if(len + 2 > size){
        fprintf(stderr, "Not enough space for titlefilename_kv");
        return len;
    }

    file = kv_val_of("file", mpd_kvptrs, len);
    title = kv_val_of("Title", mpd_kvptrs, len);

    if(file == NULL){
        return len;
    }

    filename_unix = strrchr(file, '/');
    if(filename_unix == NULL){
        filename_unix = file;
    }
    filename_unix++;
    
    
    KV_ADD("_title_or_filename", title != NULL ? title : filename_unix, mpd_kvptrs, len);
    KV_ADD("filename", filename_unix, mpd_kvptrs, len);
    return len;
}
