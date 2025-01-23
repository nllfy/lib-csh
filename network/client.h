#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../io/error.h"

void tcp_client(char ip[1024], int port, char msg[1024])
{
    int sockfd;
    struct sockaddr_in host_addr;
    socklen_t sin_size;
    char buffer[4096];

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    sin_size = sizeof(struct sockaddr_in);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(host_addr.sin_zero), '\0', 8);

    if((connect(sockfd, (struct sockaddr *)&host_addr, sin_size)) == -1)
    {
        fatal("connecting", false);
    }

    send(sockfd, msg, strlen(msg), 0);
    recv(sockfd, buffer, 4096, 0);
    close(sockfd);
}

void udp_client(char ip[48], int port, char msg[1024])
{
    int sockfd;
    struct sockaddr_in host_addr;
    socklen_t sin_size;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    sin_size = sizeof(struct sockaddr_in);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(host_addr.sin_zero), '\0', 8);

    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&host_addr, sin_size);
}