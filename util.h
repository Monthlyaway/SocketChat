#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int create_sockfd();

struct sockaddr_in *create_addr(int sockfd, char *ip, int port);

