#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "util.h"

#define INPUT_PROMPT "> "

void read_input(char *buf, int len);
void check_connection(int sockfd, struct sockaddr_in *addr);

int main(int argc, char const *argv[])
{
    // Get file descriptor for the socket
    int client_fd = create_sockfd();
    // Create connection between sockfd and sock_addr
    struct sockaddr_in *server_addr = create_addr(client_fd, "127.0.0.1", 2000);
    // Check connection with the target addr
    check_connection(client_fd, server_addr);

    char msg_sent[1024];
    while (true)
    {
        printf("%s", INPUT_PROMPT);
        read_input(msg_sent, sizeof(msg_sent));
        if (strlen(msg_sent) > 0)
        {
            int num_send = send(client_fd, msg_sent, strlen(msg_sent), 0);
        }
        else
        {
            printf("INFO: Nothing is sent\n");
        }
    }

    char msg_recv[1024];
    int num_recv = recv(client_fd, msg_recv, sizeof(msg_recv), 0);
    printf("Message received:\n");
    fwrite(msg_recv, sizeof(char), num_recv, stdout);

    return 0;
}

void read_input(char *buf, int len)
{
    fgets(buf, len, stdin);
    int input_len = strlen(buf);
    if (input_len > 0)
    {
        buf[input_len - 1] = '\0';
    }
}

void check_connection(int sockfd, struct sockaddr_in *addr)
{
    int connect_result = connect(sockfd, (struct sockaddr *)addr, sizeof(*addr));
    int port = ntohs(addr->sin_port);
    char ip[12];
    inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
    if (connect_result == 0)
    {
        printf("Success: connection with %s:%d is successful\n", ip, port);
    }
    else
    {
        printf("Error: connection with %s:%d is not successful\n", ip, port);
        exit(3);
    }
}
