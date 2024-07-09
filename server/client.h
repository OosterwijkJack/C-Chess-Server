#pragma once

#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()

#define PORT 8008
#define SA struct sockaddr

int create_client_socket();
void close_client_socket(int sockfd);