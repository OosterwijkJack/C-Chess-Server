#pragma once

#include <stdio.h>
#include <netdb.h> // network related functions and structures including htonl and htonls (used to convert bytes from host byte order to network byte order)
#include <netinet/in.h> // constants and structures for internet domain addresses contains struct sockaddr_in
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // def's for socket programming contains socket() bind() listen() accept()
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()

#define PORT 8008
#define SA struct sockaddr

int create_server_socket(void);
void write_message(int connfd, char* buff, int bsize);
char * read_message(int connfd, char* buff, int bsize);
void close_server_socket();