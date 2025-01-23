#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../io/error.h"

void tcp_server(int port, char msg[1024])
{
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;

    sin_size = sizeof(struct sockaddr_in);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', 8);

    if((bind(sockfd, (struct sockaddr *)&server_addr, sin_size)) == -1)
    {
        fatal("binding", false);
    }

    if(listen(sockfd, 20) == -1)
    {
        fatal("listening", false);
    }

    while(1)
    {
        if((new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size)) == -1)
        {
            fatal("accepting", false);
        }

        send(new_sockfd, msg, strlen(msg), 0);
        close(new_sockfd);
    }
}  

void udp_server(int port, char msg[1024])
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;

    sin_size = sizeof(struct sockaddr_in);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(server_addr.sin_zero), '\0', 8);

    if((bind(sockfd, (struct sockaddr *)&server_addr, sin_size)) == -1)
    {
        fatal("binding", false);
    }

    while(1)
    {
        if(recvfrom(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client_addr, &sin_size) == -1)
        {
            fatal("receiving", false);
        }

        sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client_addr, sin_size);
    }
}