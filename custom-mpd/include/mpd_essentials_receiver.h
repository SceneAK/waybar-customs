#ifndef MPD_ESSENTIALS_RECEIVER_H
#define MPD_ESSENTIALS_RECEIVER_H
#include <stdlib.h>

ssize_t recv_mpd_essentials(int sockfd, char *buf, size_t buf_size);

#endif
