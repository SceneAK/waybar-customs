#ifndef MPD_PARSER_H
#define MPD_PARSER_H
#include <stddef.h>
#include "../include/keyval.h"

size_t parse_to_kv(struct KeyValPtr *kvptrs, size_t kvptrs_size, char *mpdres);

#endif
