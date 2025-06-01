#ifndef MPD_RECEIVER_H
#define MPD_RECEIVER_H
#include <stdlib.h>

ssize_t recv_mpd(int sockfd, char *buffer, size_t size);
ssize_t recv_mpd_greet(int sockfd, char *buffer, size_t size);

#endif
