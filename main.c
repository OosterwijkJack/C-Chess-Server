#include <stdio.h>
#include "client.h"
#include "server.h"
#include "tools.h"
#include <stdbool.h>


#define HOST 0
#define CLIENT 1
bool serverType = NULL;

void communicate(int sockfd);

int main(int argc, char* argv[]){
    // argv checks for assigning server/client for communication
    if(argc != 2){
        puts("Usage: ./main {client/host}");
        exit(0);
    }
    
    if(strcmp(argv[1], "host") == 0){
        serverType = HOST;
    }
    else if(strcmp(argv[1], "client") == 0){
        serverType = CLIENT;
    }
    else{
        puts("Invalid arg. Input should be either \"server\" or \"client\"");
        exit(0);
    }

    // setup server
    int sockfd = 0;
    if(serverType == HOST){
        sockfd = create_server_socket();
    }
    else{
        sockfd = create_client_socket();
    }

    while(true){
        communicate(sockfd);
    }
}
/*

Create seperate functions for reading and writing so data can be retrieved as wanted

*/
void communicate(int sockfd){
    char buff[MAX];
    if(serverType == HOST){
        memset(buff, 0 , MAX);
        read_message(sockfd, buff,  sizeof(buff));
        printf("Message from client: %s\n", buff);

        memset(buff, 0, MAX);

        printf("Message to client: ");

        read_input(buff, MAX);

        if(strcmp(buff, "exit") == 0){
            memset(buff, 0, MAX);
            strcpy(buff, "*Host left*");
            write_message(sockfd, buff, sizeof(buff));
            close_server_socket();
            exit(0);
        }

        write_message(sockfd, buff, sizeof(buff));
    }
    else{
       memset(buff, 0, MAX);

       printf("Message to server: ");
       read_input(buff, MAX);

        if(strcmp(buff, "exit") == 0){
            memset(buff, 0, MAX);
            strcpy(buff, "*Client left*");
            write_message(sockfd, buff, sizeof(buff));
            close_client_socket(sockfd);
            exit(0);
        }

       write_message(sockfd, buff, sizeof(buff));
       memset(buff, 0 , MAX);
       read_message(sockfd, buff, sizeof(buff));

       printf("Message from server: %s\n", buff);
    }
}