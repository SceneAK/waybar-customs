#include <stdio.h>
#include <unistd.h>
#include "../include/mpd_receiver.h"

#define MPD_CURRENTSONG "currentsong\n"
#define MPD_STATUS "status\n"

ssize_t recv_mpd_essentials(int sockfd, char *buf, size_t buf_size)
{
    ssize_t total;
    ssize_t len;

    write(sockfd, MPD_CURRENTSONG, sizeof(MPD_CURRENTSONG) - 1);
    len = recv_mpd(sockfd, buf, buf_size-1);
    if(len <= 0){
        perror("Err mpd currentsong.\n");
        return -1;
    }
    total = len;

    write(sockfd, MPD_STATUS, sizeof(MPD_STATUS) - 1);
    len = recv_mpd(sockfd, buf + len, buf_size - len - 1);
    if(len <= 0){
        perror("Err mpd status.\n");
        return -1;
    }
    total += len;

    return total;
}
