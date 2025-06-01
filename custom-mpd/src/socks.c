#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../include/socks.h"

int create_connect_sun(char* sun_path)
{
    struct sockaddr_un addr_un;
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if(sockfd == -1) {
        perror("Failed to create unix socket\n");
        return -1;
    }

    memset(&addr_un, 0, sizeof(addr_un));
    addr_un.sun_family = AF_UNIX;
    strncpy(addr_un.sun_path, sun_path, sizeof(addr_un.sun_path)-1);

    if(connect(sockfd, (struct sockaddr *)&addr_un, sizeof(addr_un)) == -1){
        perror("Failed to connect to the socket path");
        printf("Socket Path: %s\n", addr_un.sun_path);
        close(sockfd);
        return -1;
    }
    return sockfd;
}
