#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include "util.h"


void check_bind(int sockfd, struct sockaddr_in *addr);
void receive_msg(int sockfd);
int accept_client(int sockfd);
void accept_and_receive(int welcome_fd);

int main(int argc, char const *argv[])
{
    // Create socket fd
    int welcome_fd = create_sockfd();
    // Create socket address to listen
    struct sockaddr_in *welcome_addr = create_addr(welcome_fd, "", 2000);
    // ! On the client side, we should check connection, but on server side
    // ! bind socketfd with the listening address
    check_bind(welcome_fd, welcome_addr);

    listen(welcome_fd, 10);

    // int connection_fd = accept_client(welcome_fd);
    // receive_msg(connection_fd);
    accept_and_receive(welcome_fd);

    return 0;
}

void receive_msg(int sockfd)
{
    char msg_recv[1024];
    while (true)
    {
        int num_recv = recv(sockfd, msg_recv, sizeof(msg_recv), 0);
        if (num_recv > 0)
        {
            printf("[Connection %d]: %s\n", sockfd, msg_recv);
        }
        else
        {
            break;
        }
    }
    printf("INFO: connection thread: %d is deleted\n", sockfd);
}

void check_bind(int sockfd, struct sockaddr_in *addr)
{
    int bind_result = bind(sockfd, (struct sockaddr *)addr, sizeof(*addr));
    int port = ntohs(addr->sin_port);
    char ip[12];
    inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
    if (bind_result == 0)
    {
        printf("Success: socket %d is bound with address: %s:%d\n", sockfd, ip, port);
    }
    else
    {
        printf("Error: socket %d is not bound with address: %s:%d\n", sockfd, ip, port);
    }
}

int accept_client(int sockfd)
{
    printf("INFO: Listening on welcome socket: %d\n", sockfd);
    struct sockaddr_in connection_addr;
    int connection_addr_size = sizeof(connection_addr);
    int connection_fd = accept(sockfd, (struct sockaddr *)&connection_addr, &connection_addr_size);
    return connection_fd;
}

void accept_and_receive(int welcome_fd)
{
    while (true)
    {
        int connection_fd = accept_client(welcome_fd);
        pthread_t id;
        printf("INFO: New connection thread, fd = %d\n", connection_fd);
        pthread_create(&id, NULL, receive_msg, connection_fd);
        // receive_msg(connection_fd);
    }
}
