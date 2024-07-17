#include <stdio.h>
#include "client.h"
#include "server.h"
#include "tools.h"
#include <stdbool.h>
#include <signal.h>
#include "chess.h"

#define HOST 0
#define CLIENT 1
bool serverType = NULL;

void communicate(int sockfd);
void receive_move(char buff[MAX], int * tmp, int sockfd);
void send_move(char buff[MAX], int * tmp, int sockfd);
void parse_message(int* msg, char * buff);
void parse_response(char* resp, int* out);

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

    chess_init(serverType);

    while(true){
        communicate(sockfd);
    }
}
/*

Create seperate functions for reading and writing so data can be retrieved as wanted

*/
void communicate(int sockfd){
    char buff[MAX];
    int * tmp = malloc(sizeof(int)*2);
    if(serverType == HOST){
        receive_move(buff, tmp, sockfd);
        send_move(buff, tmp, sockfd);
        
    }
    else{
        send_move(buff, tmp, sockfd);
        receive_move(buff, tmp, sockfd);
    }
}

void send_move(char buff[MAX], int * tmp, int sockfd){
    memset(buff, 0, MAX);
    // make move
    while(true){
        get_move(tmp);
        if(is_move_valid(tmp[0], tmp[1]))
            break;
        else{
            puts("Invalid move...");
        }
    }
    make_move(tmp[0], tmp[1]);
    print_board();
    parse_message(tmp, buff);
    write_message(sockfd, buff, MAX);

}
void receive_move(char buff[MAX], int * tmp, int sockfd){
    memset(buff, 0, MAX);
    memset(tmp, 0, 2);

    read_message(sockfd, buff, MAX);
    parse_response(buff, tmp);

    make_move(63-tmp[0], 63-tmp[1]);
    print_board();
}

void parse_message(int* msg, char * buff){
    sprintf(buff, "%i %i", msg[0], msg[1]);
}
void parse_response(char* resp, int* out){
    char * token = strtok(resp, " ");

    out[0] = atoi(token);
    out[1] = atoi(strtok(NULL, " ")); // continue tokenization
}