#include "../include/keyval.h"
#include "../include/mpd_to_kv.h"
#include <string.h>
#include <stdio.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int split_line(char *line, char **key, char **val)
{
    unsigned long   key_len;      
    unsigned long   val_start_i;
    unsigned long   line_len = strlen(line);

    key_len = strcspn(line, ":");
    val_start_i = key_len + 2;      /* Expected format, "Artist: Frank Sinatra\0" */

    if(key_len == line_len){
        return -1;
    }
    if(val_start_i >= line_len){
        return -1;
    }

    line[key_len] = '\0';
    *key = line;
    *val = line + val_start_i;
    return 0;
}
size_t parse_to_kv(struct KeyValPtr *kvptrs, size_t kvptrs_size, char *mpdres)
{
    char *line;
    size_t i = 0;
    
    line = strtok(mpdres, "\n");       /* thread safety no need. (i think?) */
    while(line != NULL && i < kvptrs_size)
    {
        if(split_line(line, &kvptrs[i].key, &kvptrs[i].val) == 0) {
            i++;
        }
        line = strtok(NULL, "\n");
    }
    return i;
}
