#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* MPD mainly responds in messages, so this writes c strings! */
ssize_t _recv_mpd_until(int sockfd, char *cstr_buff, size_t size,
                        int (*cond)(char *cstr, size_t recv_total))
{
    ssize_t     recv_total = 0;
    ssize_t     recved;
    while(1)
    {
        if(recv_total >= size){
            printf("Buffer not large enough");
            return -2;
        }

        recved = recv(sockfd, cstr_buff + recv_total, size - recv_total - 1, 0);
        if(recved < 0){
            perror("Failed to recieve from socket");
            return -1;
        }
        if(recved == 0){
            printf("Connection unnexpectedly closed");
            return -1;
        } 

        recv_total += recved;
        cstr_buff[recv_total] = '\0';

        if(cond(cstr_buff, recv_total)){
            return recv_total;
        }
    }
}

int ends_with_nl(char* cstr, size_t total){
    return cstr[total-1] == '\n';
}
ssize_t recv_mpd_greet(int sockfd, char *cstr_buff, size_t size)
{
    return _recv_mpd_until(sockfd, cstr_buff, size, ends_with_nl);
}

int ends_with_mpdterm(char* str, size_t total){
    int ok = strstr(str, "OK\n") != NULL;
    int ack = strncmp(str, "ACK ", 4) == 0;
    (void)total;

    return ok || ack;
}
ssize_t recv_mpd(int sockfd, char *cstr_buff, size_t size){
    return _recv_mpd_until(sockfd, cstr_buff, size, ends_with_mpdterm);
}
