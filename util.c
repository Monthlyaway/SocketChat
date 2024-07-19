#include "util.h"

int create_sockfd()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in *create_addr(int sockfd, char *ip, int port)
{
    struct sockaddr_in *addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    if (strlen(ip) == 0)
    {
        addr->sin_addr.s_addr = INADDR_ANY;
    }
    else
    {
        inet_pton(AF_INET, ip, &addr->sin_addr.s_addr);
    }
    return addr;
}




