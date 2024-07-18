#include <stdio.h>
#include "client.h"
#include "server.h"
#include "tools.h"
#include <stdbool.h>
#include <signal.h>
#include "chess.h"

#define HOST 1
#define CLIENT 0
bool serverType = NULL;

void communicate(int sockfd, int * tmp, char buff[MAX]);
void receive_move(char buff[MAX], int * tmp, int sockfd);
void send_move(char buff[MAX], int * tmp, int sockfd);
void parse_message(int* msg, char * buff);
void parse_response(char* resp, int* out);
void exit_call(int sockfd);

int main(int argc, char* argv[]){
    // argv checks for assigning server/client for communication
    signal(SIGINT, exit_call);
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

    char buff[MAX];
    int * tmp = malloc(sizeof(int)*2);
    while(true){
        communicate(sockfd, tmp, buff);
    }
}
/*

Create seperate functions for reading and writing so data can be retrieved as wanted

*/
void communicate(int sockfd, int * tmp, char buff[MAX]){
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
    memset(tmp, 0, sizeof(int)*2);
    // make move
    while(true){
        get_move(tmp);
        if(is_move_valid(tmp[0], tmp[1], serverType))
            break;
        else{
            puts("Invalid move...");
        }
    }
    printf("%i %i\n", tmp[0], tmp[1]);

    make_move(tmp[0], tmp[1]);

    board_data[tmp[1]]->moved = true;

    print_board();
    parse_message(tmp, buff);

    puts(buff);
    write_message(sockfd, buff, MAX);

}
void receive_move(char buff[MAX], int * tmp, int sockfd){
    memset(buff, 0, MAX);
    memset(tmp, 0, sizeof(int)*2);

    read_message(sockfd, buff, MAX);
    parse_response(buff, tmp);

    printf("%i %i\n", 63-tmp[0], 63-tmp[1]);

    make_move(63-tmp[0], 63-tmp[1]);
    print_board();
}

void parse_message(int* msg, char * buff){
    sprintf(buff, "%i %i\0", msg[0], msg[1]);
}
void parse_response(char* resp, int* out){
    char * token = strtok(resp, " ");

    out[0] = atoi(token);
    out[1] = atoi(strtok(NULL, " ")); // continue tokenization
}
void exit_call(int sockfd){
    if(serverType == HOST){
        close_server_socket();
        puts("Host socket closed");
    }
    else{
        close_client_socket(sockfd);
        puts("Client socket closed");
    }
    exit(0);
}