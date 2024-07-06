#include <stdio.h>
#include "client.h"
#include "server.h"
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
    if(serverType == HOST){
       char* msg = client_communicate(sockfd); //comunicate with client
       printf("Message from client: %s\n", msg);

    }
    else{
       char* msg = server_communicate(sockfd); // communicate with server
       printf("Message from server: %s\n", msg);
    }
}